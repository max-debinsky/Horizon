#include "horizon/material.h"
#include "horizon/ray_object.h"
#include "horizon/vector3.h"
#include "horizon/utility.h"
#include "horizon/texture.h"
#include <algorithm>
#include <cmath>

// ------------------ Lambertian ------------------
Lambertian::Lambertian(const color& a)
    : albedo(std::make_shared<SolidColor>(a)) {}

Lambertian::Lambertian(shared_ptr<Texture> tex)
    : albedo(tex) {}

bool Lambertian::scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();

    // Catch degenerate scatter
    if (scatter_direction.near_zero())
        scatter_direction = rec.normal;

    scattered = ray(rec.p, scatter_direction); // omit ray time
    attenuation = albedo->value(rec.u, rec.v, rec.p);
    return true;
}

// ------------------ Metal ------------------
Metal::Metal(const color& a, double f)
    : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const {
    vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    reflected = reflected + fuzz * random_unit_vector();
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}

// ------------------ Dielectric ------------------
Dielectric::Dielectric(double ri)
    : refraction_index(ri), attenuation_color(1.0,1.0,1.0) {}

Dielectric::Dielectric(double ri, const color& c)
    : refraction_index(ri), attenuation_color(c) {}

bool Dielectric::scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const {
    attenuation = attenuation_color;

    double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;
    vector3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

    vector3 direction;
    if (ri * sin_theta > 1.0 || reflectance(cos_theta, ri) > random_double())
        direction = reflect(unit_direction, rec.normal);
    else
        direction = refract(unit_direction, rec.normal, ri);

    scattered = ray(rec.p, direction);
    return true;
}

double Dielectric::reflectance(double cosine, double ri) {
    double r0 = (1 - ri) / (1 + ri);
    r0 *= r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

// ------------------ LightEmitter ------------------
LightEmitter::LightEmitter(const color& c)
    : emit_color(c) {}

bool LightEmitter::scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const {
    return false;
}

color LightEmitter::emit(const HitRecord& rec) const {
    return emit_color;
}
