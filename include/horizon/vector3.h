#pragma once

#include <cmath>
#include <iostream>

class vector3 {
public:
    double x, y, z;

    vector3();
    vector3(double _x, double _y, double _z);

    double X() const;
    double Y() const;
    double Z() const;

    vector3 operator-() const;

    vector3& operator+=(const vector3& v);
    vector3& operator*=(double t);
    vector3& operator/=(double t);

    double length_squared() const;
    double length() const;

    bool near_zero() const;
};

using point3 = vector3;

std::ostream& operator<<(std::ostream& out, const vector3& v);

vector3 operator+(const vector3& u, const vector3& v);
vector3 operator-(const vector3& u, const vector3& v);
vector3 operator*(const vector3& u, const vector3& v);
vector3 operator*(double t, const vector3& v);
vector3 operator*(const vector3& v, double t);
vector3 operator/(const vector3& v, double t);

double dot(const vector3& u, const vector3& v);
vector3 cross(const vector3& u, const vector3& v);
vector3 unit_vector(const vector3& v);
