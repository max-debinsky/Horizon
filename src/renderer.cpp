#include "horizon/material.h"
#include "horizon/renderer.h"
#include "horizon/utility.h"
#include <iostream>
#include <iomanip>

Renderer::Renderer(int image_width, int image_height, int samples_per_pixel, int max_depth)
    : width(image_width), height(image_height), samples(samples_per_pixel), max_depth(max_depth) {}

void Renderer::render(const Camera& cam, const RayObject& world, std::vector<std::vector<RGB>>& framebuffer, color skyColor) {
    framebuffer.resize(height, std::vector<RGB>(width));

    const int bar_width = 50;

    for (int j = height - 1; j >= 0; --j) {
        // Compute progress
        double progress = double(height - j) / height;
        int pos = static_cast<int>(bar_width * progress);

        // Render progress bar
        std::clog << "\r[";
        for (int i = 0; i < bar_width; ++i) {
            if (i < pos) std::clog << "=";
            else if (i == pos) std::clog << ">";
            else std::clog << " ";
        }
        std::clog << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << "% " << std::flush;

        // Render row
        for (int i = 0; i < width; ++i) {
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

    std::clog << "\r[";
    for (int i = 0; i < bar_width; ++i) std::clog << "=";
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

    ///Sky light
    vector3 unit_dir = unit_vector(r.direction());
    double t = 0.5*(unit_dir.y + 1.0);
    return skyColor; ///(1.0 - t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}