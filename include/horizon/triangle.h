#pragma once

#include "horizon/ray_object.h"
#include "horizon/material.h"
#include "horizon/vector3.h"
#include "horizon/ray.h"
#include "horizon/aabb.h"
#include "horizon/interval.h"
#include <memory>

class Triangle : public RayObject {
public:
    Triangle(const point3& v0, const point3& v1, const point3& v2,
             std::shared_ptr<Material> mat,
             const vector3* n0 = nullptr,
             const vector3* n1 = nullptr,
             const vector3* n2 = nullptr)
        : v0(v0), v1(v1), v2(v2), mat(mat)
    {
        if (n0 && n1 && n2) {
            has_normals = true;
            this->n0 = *n0;
            this->n1 = *n1;
            this->n2 = *n2;
        } else {
            has_normals = false;
            normal = unit_vector(cross(v1 - v0, v2 - v0));
        }

        vector3 min_corner(std::min({v0.x, v1.x, v2.x}),
                        std::min({v0.y, v1.y, v2.y}),
                        std::min({v0.z, v1.z, v2.z}));

        vector3 max_corner(std::max({v0.x, v1.x, v2.x}),
                        std::max({v0.y, v1.y, v2.y}),
                        std::max({v0.z, v1.z, v2.z}));


        bbox = aabb(min_corner, max_corner);
    }

    bool hit(const ray& r, interval ray_t, HitRecord& rec) const override;

    aabb bounding_box() const override { return bbox; }

private:
    point3 v0, v1, v2;
    vector3 n0, n1, n2;
    vector3 normal;
    bool has_normals;
    std::shared_ptr<Material> mat;
    aabb bbox;
};
