#include "horizon/triangle.h"
#include "horizon/utility.h"
#include "horizon/interval.h"
#include <cmath>

bool Triangle::hit(const ray& r, interval ray_t, HitRecord& rec) const {
    const double EPSILON = 1e-8;
    vector3 edge1 = v1 - v0;
    vector3 edge2 = v2 - v0;
    vector3 h = cross(r.direction(), edge2);
    double a = dot(edge1, h);

    if (fabs(a) < EPSILON)
        return false; // Ray parallel to triangle

    double f = 1.0 / a;
    vector3 s = r.origin() - v0;
    double u = f * dot(s, h);
    if (u < 0.0 || u > 1.0)
        return false;

    vector3 q = cross(s, edge1);
    double v = f * dot(r.direction(), q);
    if (v < 0.0 || u + v > 1.0)
        return false;

    double t = f * dot(edge2, q);
    if (t < ray_t.min || t > ray_t.max)
        return false;

    rec.t = t;
    rec.p = r.at(t);
    rec.mat = mat;

    if (has_normals) {
        rec.normal = unit_vector((1 - u - v) * n0 + u * n1 + v * n2);
    } else {
        rec.normal = normal;
    }

    rec.front_face = dot(r.direction(), rec.normal) < 0;
    if (!rec.front_face)
        rec.normal = -rec.normal;

    return true;
}
