#include "horizon/aabb.h"

const aabb aabb::empty    = aabb(interval::empty,    interval::empty,    interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

aabb::aabb() : x(), y(), z() {}

aabb::aabb(const interval& x, const interval& y, const interval& z)
    : x(x), y(y), z(z) {}

aabb::aabb(const point3& a, const point3& b) {
    x = (a.x <= b.x) ? interval(a.x, b.x) : interval(b.x, a.x);
    y = (a.y <= b.y) ? interval(a.y, b.y) : interval(b.y, a.y);
    z = (a.z <= b.z) ? interval(a.z, b.z) : interval(b.z, a.z);
}

aabb::aabb(const aabb& box0, const aabb& box1) {
    x = interval(std::fmin(box0.x.min, box1.x.min), std::fmax(box0.x.max, box1.x.max));
    y = interval(std::fmin(box0.y.min, box1.y.min), std::fmax(box0.y.max, box1.y.max));
    z = interval(std::fmin(box0.z.min, box1.z.min), std::fmax(box0.z.max, box1.z.max));
}

const interval& aabb::axis_interval(int n) const {
    if (n == 1) return y;
    if (n == 2) return z;
    return x;
}

bool aabb::hit(const ray& r, interval ray_t) const {
    const point3& ray_orig = r.origin();
    const vector3& ray_dir = r.direction();

    for (int axis = 0; axis < 3; axis++) {
        const interval& ax = axis_interval(axis);
        double adinv = 1.0 / ray_dir[axis];

        double t0 = (ax.min - ray_orig[axis]) * adinv;
        double t1 = (ax.max - ray_orig[axis]) * adinv;

        if (t0 > t1) std::swap(t0, t1);

        ray_t.min = t0 > ray_t.min ? t0 : ray_t.min;
        ray_t.max = t1 < ray_t.max ? t1 : ray_t.max;

        if (ray_t.max <= ray_t.min)
            return false;
    }
    return true;
}
