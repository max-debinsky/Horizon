#pragma once

#include "horizon/ray.h"
#include "horizon/vector3.h"
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

// Time interval for ray parameter
struct Interval {
    double min;
    double max;
    Interval(double mi, double ma) : min(mi), max(ma) {}
};

class RayObject {
public:
    virtual ~RayObject() = default;

    virtual bool hit(const ray& r, Interval ray_t, HitRecord& rec) const = 0;
};
