#include "horizon/color.h"

double linear_to_gamma(double linear_component) {
    if (linear_component <= 0.0) return 0.0;
    return std::sqrt(linear_component);
}

static inline double clamp(double x, double min_val, double max_val) {
    if (x < min_val) return min_val;
    if (x > max_val) return max_val;
    return x;
}

RGB write_color(const color& pixel_color) {
    double r = linear_to_gamma(pixel_color.x());
    double g = linear_to_gamma(pixel_color.y());
    double b = linear_to_gamma(pixel_color.z());

    RGB px;
    px.r = static_cast<unsigned char>(256 * clampd(r, 0.0, 0.999));
    px.g = static_cast<unsigned char>(256 * clampd(g, 0.0, 0.999));
    px.b = static_cast<unsigned char>(256 * clampd(b, 0.0, 0.999));

    return px;
}
