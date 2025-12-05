#pragma once

#include "horizon/vector3.h"
#include <cmath>
#include <random>

#ifndef M_PI
constexpr double M_PI = 3.14159265358979323846;
#endif

double random_double();

double random_double(double min, double max);

vector3 random_in_unit_sphere();

vector3 random_in_unit_disk();

vector3 random_unit_vector();

vector3 reflect(const vector3& v, const vector3& n);

vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat);

inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

