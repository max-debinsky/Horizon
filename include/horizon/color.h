#pragma once

#include "horizon/vector3.h"

#include <iostream>
#include <cmath>

using color = vector3;

double linear_to_gamma(double linear_component);

void write_color(std::ostream& out, const color& pixel_color);
