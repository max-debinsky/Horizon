#include "horizon/output.h"
#include <iostream>

int main() {
    const int width = 600;
    const int height = 400;

    std::vector<std::vector<RGB>> framebuffer(height, std::vector<RGB>(width));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            framebuffer[y][x] = { (unsigned char)x, (unsigned char)y, 128 };
        }
    }

    save_png("render.png", width, height, framebuffer);

    return 0;
}
