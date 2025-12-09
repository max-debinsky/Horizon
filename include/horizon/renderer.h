#pragma once

#include "horizon/camera.h"
#include "horizon/ray_object.h"
#include "horizon/vector3.h"
#include "horizon/color.h"
#include "horizon/utility.h"

#include <vector>
#include <atomic>

class Renderer {
public:
    Renderer(int image_width, int image_height, int samples_per_pixel, int max_depth, int tile_size = 32);

    void render(const Camera& cam, const RayObject& world,
                std::vector<std::vector<RGB>>& framebuffer, color skyColor);

private:
    int width;
    int height;
    int samples;
    int max_depth;
    int tile_size;

    color ray_color(const ray& r, int depth, const RayObject& world, color skyColor) const;
};
