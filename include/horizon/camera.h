#pragma once

#include "horizon/vector3.h"
#include "horizon/ray.h"

class Camera {
public:
    Camera(
        point3 lookfrom,
        point3 lookat,
        vector3 vup,
        double vfov,
        double aspect_ratio,
        double defocus_angle = 0.0,
        double focus_dist = 10.0
    );

    ray get_ray(double u, double v) const;

private:
    point3 origin;
    vector3 u, v, w;
    vector3 horizontal, vertical;
    point3 lower_left_corner;

    double lens_radius;
};
