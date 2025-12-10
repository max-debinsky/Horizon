#include "horizon/camera.h"
#include "horizon/renderer.h"
#include "horizon/object_group.h"
#include "horizon/material.h"
#include "horizon/vector3.h"
#include "horizon/rgb.h"
#include "horizon/output.h"
#include "horizon/utility.h"
#include "horizon/sphere.h"
#include "horizon/bvh.h"
#include "horizon/texture.h"

#include <memory>
#include <vector>
#include <iostream>
#include <conio.h>
#include <algorithm>

std::shared_ptr<Material> MakeMaterial(const std::string& name) {
    std::string key = name;
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

    if (key == "ground") {
        return std::make_shared<Lambertian>(color(0.5, 0.5, 0.5));
    }
    if (key == "red") {
        return std::make_shared<Lambertian>(color(0.8, 0.1, 0.1));
    }
    if (key == "green") {
        return std::make_shared<Lambertian>(color(0.1, 0.8, 0.1));
    }
    if (key == "blue") {
        return std::make_shared<Lambertian>(color(0.1, 0.1, 0.8));
    }
    if (key == "yellow") {
        return std::make_shared<Lambertian>(color(0.9, 0.9, 0.2));
    }
    if (key == "metal" || key == "mirror") {
        return std::make_shared<Metal>(color(0.8, 0.8, 0.6), 0.0); 
    }
    if (key == "silver") {
    return std::make_shared<Metal>(color(0.9, 0.9, 0.9), 0.0); 
    }
    if (key == "glass") {
        return std::make_shared<Dielectric>(1.5);
    }
    if (key == "bubble" || key == "blueice") {
        return std::make_shared<Dielectric>(1.00 / 1.50);
    }
    if (key == "light" || key == "emissive") {
        return std::make_shared<LightEmitter>(color(4, 4, 4));
    }
    if (key == "purplelight") {
        return std::make_shared<LightEmitter>(color(0.36328125, 0.24609375, 0.82421875));
    }

    // Default material if unknown
    return std::make_shared<Lambertian>(color(0.7, 0.7, 0.7));
}

void scene1(ObjectGroup& _world){
    // Ground
    _world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, MakeMaterial("ground"))); // large ground sphere

    // Main scene spheres
    _world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, MakeMaterial("glass")));
    _world.add(std::make_shared<Sphere>(point3(0, 1, 0), 0.8, MakeMaterial("bubble")));
    _world.add(std::make_shared<Sphere>(point3(-2, 0.7, 0), 0.7, MakeMaterial("light")));
    _world.add(std::make_shared<Sphere>(point3(2, 1.2, 0), 1.2, MakeMaterial("green")));
    _world.add(std::make_shared<Sphere>(point3(-3, 2, -5), 2.0, MakeMaterial("silver")));

    _world.add(std::make_shared<Sphere>(point3(1.6, 0.3, 1.5), 0.3, MakeMaterial("purplelight")));
}

void scene2(ObjectGroup& _world){
    // Ground
    auto checker = std::make_shared<CheckerTexture>(
    1.0,                // size / scale of the checkers
    color(0.9, 0.9, 0.9), // color for “even” squares
    color(0.1, 0.1, 0.1)  // color for “odd” squares
    );
    auto mat = std::make_shared<Lambertian>(checker);
    _world.add(std::make_shared<Sphere>(point3(0, -20, 0), 20, mat)); // large ground sphere

    // Sun
    _world.add(std::make_shared<Sphere>(point3(-0.6946, 5, 20), 10, MakeMaterial("light")));

    // Main scene spheres
    //_world.add(std::make_shared<Sphere>(point3(0, 1, 0), 0.2, MakeMaterial("red"))); // center

    auto checker2 = std::make_shared<CheckerTexture>(
    0.1,                // size / scale of the checkers
    color(0.2, 0.2, 0.9), // color for “even” squares
    color(0.1, 0.1, 0.4)  // color for “odd” squares
    );
    auto mat2 = std::make_shared<Lambertian>(checker2);

    _world.add(std::make_shared<Sphere>(point3(-3.7588, 0.6, -1.3681), 0.6, mat2));
    _world.add(std::make_shared<Sphere>(point3(-2.5712, 0.5, -3.0642), 0.5, MakeMaterial("green")));
    _world.add(std::make_shared<Sphere>(point3(-0.6946, 0.7, -3.9392), 0.7, mat2));
    _world.add(std::make_shared<Sphere>(point3(1.3681, 0.4, -3.7588), 0.4, MakeMaterial("glass")));
    _world.add(std::make_shared<Sphere>(point3(1.3681, 0.4, -3.7588), 0.3, MakeMaterial("bubble")));
    _world.add(std::make_shared<Sphere>(point3(3.0642, 0.9, -2.5712), 0.9, MakeMaterial("metal")));
}

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 1000;
    const int max_depth = 50;

    // World (scene container)
    ObjectGroup world;
    scene2(world); // populate first

    auto bvh_root = std::make_shared<BVHNode>(world.get_objects());

    // Camera
    point3 lookfrom(3,3,-10);
    point3 lookat(0,1,0);
    vector3 vup(0,1,0);
    double vfov = 30.0;
    double focus_dist = 11.66;
    double defocus_angle = 0.0f;

    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, defocus_angle, focus_dist);
    
    // Renderer
    Renderer renderer(image_width, image_height, samples_per_pixel, max_depth);
    std::vector<std::vector<RGB>> framebuffer;

    renderer.render(cam, world, framebuffer, color(0,0,0));

    // Save to PNG
    save_png("render.png", image_width, image_height, framebuffer);

    std::cout << "Press any key to exit...";
    _getch();
    return 0;
}
