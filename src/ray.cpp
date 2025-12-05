#include "horizon/ray.h"

ray::ray() : tm(0) {}

ray::ray(const point3& origin, const vector3& direction)
    : orig(origin), dir(direction) {}

const point3& ray::origin() const { return orig; }
const vector3& ray::direction() const { return dir; }

point3 ray::at(double t) const {
    return orig + t * dir;
}
