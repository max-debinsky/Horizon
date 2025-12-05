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
    explicit Dielectric(double refraction_index);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    double refraction_index;

    static double reflectance(double cosine, double refraction_index);
};
