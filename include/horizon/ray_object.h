#pragma once

#include "horizon/ray.h"
#include "horizon/vector3.h"
#include "horizon/interval.h"
#include <memory>

using std::shared_ptr;

class Material; // forward declaration

struct HitRecord {
    point3 p;
    vector3 normal;
    shared_ptr<Material> mat;
    double t;
    bool front_face;

    void set_face_normal(const ray& r, const vector3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class RayObject {
public:
    virtual ~RayObject() = default;

    virtual bool hit(const ray& r, interval ray_t, HitRecord& rec) const = 0;
};
