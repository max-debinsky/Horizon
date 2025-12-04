#pragma once

class vector3 {
    double x, y, z;

    vector3() : x(0), y(0), z(0) {};
    vector3(double _x, double _y, double _z) : x(0), y(0), z(0) {};

    double x() const { return x; }
    double y() const { return y; }
    double z() const { return z; }

    vector3 operator-() const { return vector3(-x, -y, -z); }

    vector3& operator+=(const vector3& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vector3& operator*=(double t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vector3& operator/=(double t) {
        return *this *= 1 / t;
    }
};