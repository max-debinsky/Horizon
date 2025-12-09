#pragma once

#include "horizon/ray_object.h"
#include "horizon/material.h"
#include "horizon/vector3.h"
#include "horizon/ray.h"
#include "horizon/aabb.h"

#include <memory>

class Sphere : public RayObject {
public:
    Sphere(const point3& center, double radius, std::shared_ptr<Material> mat)
        : center(center),
          radius(std::fmax(0.0, radius)),
          mat(mat)
    {
        vector3 r(radius, radius, radius);
        bbox = aabb(center - r, center + r);
    }

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override { return bbox; }

private:
    point3 center;
    double radius;
    std::shared_ptr<Material> mat;
    aabb bbox;
};
