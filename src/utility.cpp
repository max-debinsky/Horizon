#include "horizon/utility.h"
#include <random>

static std::uniform_real_distribution<double> distribution(0.0, 1.0);
static std::mt19937 generator(std::random_device{}());

double random_double() {
    return distribution(generator);
}

vector3 random_in_unit_sphere() {
    while (true) {
        vector3 p(random_double() * 2 - 1, random_double() * 2 - 1, random_double() * 2 - 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vector3 random_in_unit_disk() {
    while (true) {
        vector3 p(random_double() * 2 - 1, random_double() * 2 - 1, 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vector3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vector3 reflect(const vector3& v, const vector3& n) {
    return v - 2 * dot(v, n) * n;
}

vector3 refract(const vector3& uv, const vector3& n, double etai_over_etat) {
    double cos_theta = std::fmin(dot(-uv, n), 1.0);
    vector3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    vector3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}
