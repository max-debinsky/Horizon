#include "horizon/color.h"
#include "horizon/rgb.h"

double linear_to_gamma(double linear_component) {
    if (linear_component <= 0.0) return 0.0;
    return std::sqrt(linear_component);
}

static inline double clamp(double x, double min_val, double max_val) {
    if (x < min_val) return min_val;
    if (x > max_val) return max_val;
    return x;
}

RGB to_rgb(const color& pixel_color) {
    double r = linear_to_gamma(pixel_color.X());
    double g = linear_to_gamma(pixel_color.Y());
    double b = linear_to_gamma(pixel_color.Z());

    RGB px;
    px.r = static_cast<unsigned char>(256 * clamp(r, 0.0, 0.999));
    px.g = static_cast<unsigned char>(256 * clamp(g, 0.0, 0.999));
    px.b = static_cast<unsigned char>(256 * clamp(b, 0.0, 0.999));

    return px;
}
