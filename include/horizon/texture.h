#pragma once

#include "horizon/color.h"

class Texture {
public:
    virtual ~Texture() = default;

    // Return the color value of the texture at coordinates (u,v) on point p
    virtual color value(double u, double v, const point3& p) const = 0;
};

class SolidColor : public Texture {
public:
    // Constructors
    SolidColor(const color& c) : albedo(c) {}
    SolidColor(double red, double green, double blue) : albedo(red, green, blue) {}

    // Override value to always return the solid color
    color value(double u, double v, const point3& p) const override {
        return albedo;
    }

private:
    color albedo;
};
