#pragma once

#include "horizon/vector3.h"

class ray {
public:
    ray();

    ray(const point3& origin, const vector3& direction);

    const point3& origin() const;
    const vector3& direction() const;

    point3 at(double t) const;

private:
    point3 orig;
    vector3 dir;
    double tm;
};