#pragma once

#include "horizon/ray_object.h"
#include "horizon/vector3.h"
#include "horizon/utility.h"
#include "horizon/texture.h"
#include <algorithm>
#include <cmath>

using std::shared_ptr;

struct HitRecord;

// ------------------ Base Material ------------------
class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const {
        return false;
    }

    virtual color emit(const HitRecord& rec) const {
        return color(0,0,0);
    }
};

// ------------------ Lambertian ------------------
class Lambertian : public Material {
public:
    // Lambertian can be constructed with either a solid color or a texture
    Lambertian(const color& a);
    Lambertian(shared_ptr<Texture> tex);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    shared_ptr<Texture> albedo;
};

// ------------------ Metal ------------------
class Metal : public Material {
public:
    Metal(const color& a, double f);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    color albedo;
    double fuzz;
};

// ------------------ Dielectric ------------------
class Dielectric : public Material {
public:
    Dielectric(double ri);
    Dielectric(double ri, const color& c);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;

private:
    double refraction_index;
    color attenuation_color;

    static double reflectance(double cosine, double ri);
};

// ------------------ LightEmitter ------------------
class LightEmitter : public Material {
public:
    LightEmitter(const color& c);

    bool scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;
    color emit(const HitRecord& rec) const override;

private:
    color emit_color;
};
