#pragma once

#include "horizon/vector3.h"
#include <cmath>
#include <random>

double random_double();

vector3 random_in_unit_sphere();

vector3 random_unit_vector();

vector3 reflect(const vector3& v, const vector3& n);

vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat);
