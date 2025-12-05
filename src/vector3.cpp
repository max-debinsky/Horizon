#include "horizon/vector3.h"
#include "horizon/utility.h"

vector3::vector3() : x(0), y(0), z(0) {}
vector3::vector3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

double vector3::X() const { return x; }
double vector3::Y() const { return y; }
double vector3::Z() const { return z; }

vector3 vector3::operator-() const { return vector3(-x, -y, -z); }

vector3& vector3::operator+=(const vector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vector3& vector3::operator*=(double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

vector3& vector3::operator/=(double t) {
    return *this *= 1 / t;
}

double vector3::length_squared() const {
    return x*x + y*y + z*z;
}

double vector3::length() const {
    return std::sqrt(length_squared());
}

std::ostream& operator<<(std::ostream& out, const vector3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

vector3 operator+(const vector3& u, const vector3& v) {
    return vector3(u.x + v.x, u.y + v.y, u.z + v.z);
}

vector3 operator-(const vector3& u, const vector3& v) {
    return vector3(u.x - v.x, u.y - v.y, u.z - v.z);
}

vector3 operator*(const vector3& u, const vector3& v) {
    return vector3(u.x * v.x, u.y * v.y, u.z * v.z);
}

vector3 operator*(double t, const vector3& v) {
    return vector3(t*v.x, t*v.y, t*v.z);
}

vector3 operator*(const vector3& v, double t) {
    return t * v;
}

vector3 operator/(const vector3& v, double t) {
    return (1/t) * v;
}

double dot(const vector3& u, const vector3& v) {
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

vector3 cross(const vector3& u, const vector3& v) {
    return vector3(u.y*v.z - u.z*v.y,
                   u.z*v.x - u.x*v.z,
                   u.x*v.y - u.y*v.x);
}

vector3 unit_vector(const vector3& v) {
    return v / v.length();
}

bool vector3::near_zero() const {
    const auto s = 1e-8;
    return (std::fabs(x) < s) && (std::fabs(y) < s) && (std::fabs(z) < s);
}

vector3 vector3::random() {
    return vector3(random_double(), random_double(), random_double());
}

vector3 vector3::random(double min, double max) {
    return vector3(min + (max - min) * random_double(),
                   min + (max - min) * random_double(),
                   min + (max - min) * random_double());
}