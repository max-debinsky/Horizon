#pragma once
#include <string>
#include <vector>

struct RGB {
    unsigned char r, g, b;
};

bool save_png(const std::string& filename, int width, int height, const std::vector<std::vector<RGB>>& pixels);