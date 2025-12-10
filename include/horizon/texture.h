#pragma once

#include "horizon/color.h"
#include <memory>
#include <cmath>

using std::shared_ptr;

class Texture {
public:
    virtual ~Texture() = default;

    // Return the color value of the texture at coordinates (u,v) on point p
    virtual color value(double u, double v, const point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    SolidColor(const color& c) : albedo(c) {}
    SolidColor(double r, double g, double b) : albedo(r, g, b) {}

    color value(double u, double v, const point3& p) const override {
        return albedo;
    }

private:
    color albedo;
};

class CheckerTexture : public Texture {
public:
    CheckerTexture(double scale, shared_ptr<Texture> even, shared_ptr<Texture> odd)
        : inv_scale(1.0 / scale), even(even), odd(odd) {}

    CheckerTexture(double scale, const color& c1, const color& c2)
        : CheckerTexture(scale, std::make_shared<SolidColor>(c1), std::make_shared<SolidColor>(c2)) {}

    color value(double u, double v, const point3& p) const override {
        int xInt = static_cast<int>(std::floor(inv_scale * p.x));
        int yInt = static_cast<int>(std::floor(inv_scale * p.y));
        int zInt = static_cast<int>(std::floor(inv_scale * p.z));

        bool isEven = (xInt + yInt + zInt) % 2 == 0;
        return isEven ? even->value(u, v, p) : odd->value(u, v, p);
    }

private:
    double inv_scale;
    shared_ptr<Texture> even;
    shared_ptr<Texture> odd;
};
