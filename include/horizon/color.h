#pragma once

#include "horizon/vector3.h"
#include "horizon/rgb.h"

#include <iostream>
#include <cmath>

using color = vector3;

double linear_to_gamma(double linear_component);

RGB to_rgb(const color& pixel_color);
