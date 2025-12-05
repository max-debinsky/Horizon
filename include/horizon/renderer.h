#pragma once

#include "horizon/camera.h"
#include "horizon/ray_object.h"
#include "horizon/color.h"
#include <ostream>

class Renderer {
public:
    Renderer(int image_width, int image_height, int samples_per_pixel, int max_depth);

    void render(const Camera& cam, const RayObject& world, std::ostream& out);

private:
    int width;
    int height;
    int samples;
    int max_depth;

    color ray_color(const ray& r, int depth, const RayObject& world) const;
};
