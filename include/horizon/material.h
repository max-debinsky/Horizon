#pragma once

#include "horizon/ray_object.h"
#include "horizon/ray.h"
#include "horizon/color.h"
#include "horizon/vector3.h"

class Material {
public:
    virtual ~Material() = default;

    // Returns true if ray is scattered, also sets attenuation and scattered ray
    virtual bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const;

    virtual color emit(const HitRecord& rec) const;
};

class Lambertian : public Material {
public:
    Lambertian(const color& albedo);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    color albedo;
};

class Metal : public Material {
public:
    Metal(const color& albedo, double fuzz);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    color albedo;
    double fuzz;
};

class Dielectric : public Material {
public:
    Dielectric(double ri, const color& color_attenuation = color(1.0,1.0,1.0))
        : refraction_index(ri), attenuation_color(color_attenuation) {}

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    double refraction_index;
    color attenuation_color;

    static double reflectance(double cosine, double refraction_index);
};

class LightEmitter : public Material {
public:
    LightEmitter(const color& color) : emit_color(color) {}
    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;
    color emit(const HitRecord& rec) const override;

private:
    color emit_color;
};