#pragma once

#include "horizon/rgb.h"

#include <string>
#include <vector>

bool save_png(const std::string& filename, int width, int height, const std::vector<std::vector<RGB>>& pixels);