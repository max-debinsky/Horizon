#include "horizon/sphere.h"
#include <cmath>

Sphere::Sphere(const point3& center, double radius, std::shared_ptr<Material> mat)
    : center_motion(center, vector3(0,0,0)), radius(std::fmax(0, radius)), mat(mat) {}

Sphere::Sphere(const point3& center0, const point3& center1, double radius, std::shared_ptr<Material> mat)
    : center_motion(center0, center1 - center0), radius(std::fmax(0, radius)), mat(mat) {}

point3 Sphere::center_at(double time) const {
    // Linear interpolation for moving sphere
    return center_motion.origin() + time * center_motion.direction();
}

bool Sphere::hit(const ray& r, Interval ray_t, HitRecord& rec) const {
    point3 current_center = center_at(r.time());
    vector3 oc = r.origin() - current_center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;

    auto sqrtd = std::sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (!ray_t.surrounds(root)) {
        root = (-half_b + sqrtd) / a;
        if (!ray_t.surrounds(root)) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vector3 outward_normal = (rec.p - current_center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;

    return true;
}
