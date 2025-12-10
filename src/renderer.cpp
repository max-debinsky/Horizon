#include "horizon/material.h"
#include "horizon/renderer.h"
#include "horizon/utility.h"
#include "horizon/color.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <future>
#include <algorithm>

Renderer::Renderer(int image_width, int image_height, int samples_per_pixel, int max_depth, int tile_size)
    : width(image_width), height(image_height), samples(samples_per_pixel), max_depth(max_depth), tile_size(tile_size) {}

void Renderer::render(const Camera& cam, const RayObject& world, std::vector<std::vector<RGB>>& framebuffer, color skyColor) {
    framebuffer.resize(height, std::vector<RGB>(width));

    const int num_threads = std::max(1u, std::thread::hardware_concurrency() - 1);
    std::vector<std::future<void>> futures;
    std::atomic<int> tiles_done(0);

    // Generate tiles
    std::vector<std::pair<int,int>> tiles;
    for (int y = 0; y < height; y += tile_size) {
        for (int x = 0; x < width; x += tile_size) {
            tiles.emplace_back(x, y);
        }
    }

    const int total_tiles = static_cast<int>(tiles.size());

    auto render_tile = [&](int start_idx, int end_idx) {
        for (int idx = start_idx; idx < end_idx; ++idx) {
            int tx = tiles[idx].first;
            int ty = tiles[idx].second;
            int tile_w = std::min(tile_size, width - tx);
            int tile_h = std::min(tile_size, height - ty);

            for (int j = ty; j < ty + tile_h; ++j) {
                for (int i = tx; i < tx + tile_w; ++i) {
                    color pixel_color(0, 0, 0);
                    for (int s = 0; s < samples; ++s) {
                        double u = (i + random_double()) / (width - 1);
                        double v = (j + random_double()) / (height - 1);
                        ray r = cam.get_ray(u, v);
                        pixel_color += ray_color(r, max_depth, world, skyColor);
                    }
                    framebuffer[height - j - 1][i] = to_rgb(pixel_color / static_cast<double>(samples));
                }
            }

            // Update progress bar
            int done = ++tiles_done;
            double progress = double(done) / total_tiles;
            const int bar_width = 50;
            int pos = static_cast<int>(bar_width * progress);

            std::clog << "\r[";
            for (int k = 0; k < bar_width; ++k) {
                if (k < pos) std::clog << "=";
                else if (k == pos) std::clog << ">";
                else std::clog << " ";
            }
            std::clog << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << "% " << std::flush;
        }
    };

    // Split tiles into thread ranges
    int tiles_per_thread = (total_tiles + num_threads - 1) / num_threads;
    for (int t = 0; t < num_threads; ++t) {
        int start_idx = t * tiles_per_thread;
        int end_idx = std::min(start_idx + tiles_per_thread, total_tiles);
        if (start_idx >= end_idx) break;
        futures.push_back(std::async(std::launch::async, render_tile, start_idx, end_idx));
    }

    // Wait for all threads
    for (auto& f : futures) f.get();

    std::clog << "\r[";
    for (int i = 0; i < 50; ++i) std::clog << "=";
    std::clog << "] 100.0% Done!\n";
}

color Renderer::ray_color(const ray& r, int depth, const RayObject& world, color skyColor) const {
    if (depth <= 0)
        return color(0,0,0);

    HitRecord rec;
    if (world.hit(r, interval(0.001, 1e10), rec)) {
        ray scattered;
        color attenuation;
        color emitted = rec.mat->emit(rec);
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world, skyColor);
        return emitted;
    }

    return skyColor;
}
