#pragma once

#include "horizon/interval.h"
#include "horizon/vector3.h"
#include "horizon/ray.h"

class aabb {
public:
    interval x, y, z;

    aabb();
    aabb(const interval& x, const interval& y, const interval& z);
    aabb(const point3& a, const point3& b);
    aabb(const aabb& box0, const aabb& box1);

    const interval& axis_interval(int n) const;
    bool hit(const ray& r, interval ray_t) const;

    double width() const { return x.size(); }
    double height() const { return y.size(); }
    double depth() const { return z.size(); }

    int longest_axis() const {
        double w = width();
        double h = height();
        double d = depth();
        if (w > h)
            return w > d ? 0 : 2;
        else
            return h > d ? 1 : 2;
    }

    static const aabb empty;
    static const aabb universe;
};
