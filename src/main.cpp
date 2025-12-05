#include "horizon/camera.h"
#include "horizon/renderer.h"
#include "horizon/object_group.h"
#include "horizon/material.h"
#include "horizon/vector3.h"
#include "horizon/rgb.h"
#include "horizon/output.h"
#include "horizon/utility.h"
#include "horizon/sphere.h"

#include <memory>
#include <vector>
#include <iostream>

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 200;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;
    const int max_depth = 50;

    // World (scene container)
    ObjectGroup world;

    // Materials
    auto material_ground   = std::make_shared<Lambertian>(color(0.5, 0.5, 0.5)); // gray ground
    auto material_red      = std::make_shared<Lambertian>(color(0.8, 0.1, 0.1)); // red diffuse
    auto material_green    = std::make_shared<Lambertian>(color(0.1, 0.8, 0.1)); // green diffuse
    auto material_blue     = std::make_shared<Lambertian>(color(0.1, 0.1, 0.8)); // blue diffuse
    auto material_metal    = std::make_shared<Metal>(color(0.8, 0.8, 0.6), 0.0); // mirror
    auto material_glass    = std::make_shared<Dielectric>(1.5);                  // glass
    auto material_small    = std::make_shared<Lambertian>(color(0.9, 0.9, 0.2)); // yellow small

    // Ground
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, material_ground)); // large ground sphere

    // Main scene spheres
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material_glass));      // big glass sphere center
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 0.8, material_glass));      // big glass sphere center
    world.add(std::make_shared<Sphere>(point3(-2, 1, 0), 1.0, material_metal));       // red diffuse
    world.add(std::make_shared<Sphere>(point3(2, 1, 0), 1.0, material_red));      // metallic sphere


    // Camera
    point3 lookfrom(6,3,10);
    point3 lookat(0,1,0);
    vector3 vup(0,1,0);
    double vfov = 20.0;
    double focus_dist = 10.0;
    double defocus_angle = 0.0;

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, defocus_angle, focus_dist);
    
    // Renderer
    Renderer renderer(image_width, image_height, samples_per_pixel, max_depth);
    std::vector<std::vector<RGB>> framebuffer;

    renderer.render(cam, world, framebuffer);

    // Save to PNG
    if (save_png("render.png", image_width, image_height, framebuffer)) {
        std::cout << "Saved render.png successfully.\n";
    } else {
        std::cerr << "Failed to save render.png.\n";
    }

    return 0;
}
