#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include "horizon/output.h"

#include <vector>
#include <iostream>

bool save_png(const std::string& filename, int width, int height, const std::vector<std::vector<RGB>>& pixels) {
    std::vector<unsigned char> buffer(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * 3;
            buffer[i + 0] = pixels[y][x].r;
            buffer[i + 1] = pixels[y][x].g;
            buffer[i + 2] = pixels[y][x].b;
        }
    }

    if (stbi_write_png(filename.c_str(), width, height, 3, buffer.data(), width * 3)) {
        std::cout << "Saved " << filename << "\n";
        return true;
    } else {
        std::cerr << "Failed to save " << filename << "\n";
        return false;
    }
}
