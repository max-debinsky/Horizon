#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <iostream>

int main() {
    const int width = 256;
    const int height = 256;

    // Allocate pixel array
    unsigned char* pixels = new unsigned char[width * height * 3];

    // Fill pixel array
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = (y * width + x) * 3;
            pixels[index + 0] = (unsigned char)x;
            pixels[index + 1] = (unsigned char)y;
            pixels[index + 2] = 128;
        }
    }

    // Save as PNG
    if (stbi_write_png("output.png", width, height, 3, pixels, width * 3)) {
        std::cout << "Saved image as output.png\n";
    } else {
        std::cout << "Failed to save image\n";
    }

    delete[] pixels;
    return 0;
}
