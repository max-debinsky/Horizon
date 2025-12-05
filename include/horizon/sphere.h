#pragma once

#include "horizon/ray_object.h"
#include "horizon/material.h"
#include "horizon/vector3.h"
#include "horizon/ray.h"
#include "horizon/utility.h"
#include <memory>

class Sphere : public RayObject {
public:
    Sphere(const point3& center, double radius, std::shared_ptr<Material> mat);

    // Moving sphere
    Sphere(const point3& center0, const point3& center1, double radius, std::shared_ptr<Material> mat);

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

private:
    ray center_motion;
    double radius;
    std::shared_ptr<Material> mat;

    point3 center_at(double time) const;
};
