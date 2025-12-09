#pragma once

#include "vector3.h"
#include <cmath>
#include <random>

double random_double();
double random_double(double min, double max);

int random_int(int min, int max);  // ← new function

vector3 random_in_unit_sphere();
vector3 random_in_unit_disk();
vector3 random_unit_vector();

vector3 reflect(const vector3& v, const vector3& n);
vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat);


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
inline double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}