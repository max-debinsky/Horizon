#include "horizon/output.h"
#include "horizon/color.h"
#include "horizon/vector3.h"
#include "horizon/rgb.h"

#include <iostream>

int main() {
    const int width = 600;
    const int height = 400;

    std::vector<std::vector<RGB>> framebuffer(height, std::vector<RGB>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            color c(
                double(x) / width,   // R
                double(y) / height,  // G
                0.5                  // B
            );

            framebuffer[y][x] = to_rgb(c);
        }
    }

    save_png("render.png", width, height, framebuffer);

    return 0;
}
