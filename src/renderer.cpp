#include "horizon/renderer.h"
#include "horizon/utility.h"
#include <iostream>

Renderer::Renderer(int image_width, int image_height, int samples_per_pixel, int max_depth)
    : width(image_width), height(image_height), samples(samples_per_pixel), max_depth(max_depth) {}

void Renderer::render(const Camera& cam, const RayObject& world, std::ostream& out) {
    out << "P3\n" << width << ' ' << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
        std::clog << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples; ++s) {
                auto u = (i + random_double()) / (width - 1);
                auto v = (j + random_double()) / (height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(out, pixel_color, samples);
        }
    }
    std::clog << "\rDone.                 \n";
}

color Renderer::ray_color(const ray& r, int depth, const RayObject& world) const {
    if (depth <= 0)
        return color(0,0,0);

    HitRecord rec;
    if (world.hit(r, Interval(0.001, 1e10), rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth-1, world);
        return color(0,0,0);
    }

    vec3 unit_dir = unit_vector(r.direction());
    double t = 0.5*(unit_dir.y + 1.0);
    return (1.0 - t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0);
}
