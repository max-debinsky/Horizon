#pragma once

class interval {
public:
    double min;
    double max;

    interval() : min(0), max(0) {}
    interval(double min, double max) : min(min), max(max) {}

    double size() const { return max - min; }

    bool surrounds(double t) const { return t >= min && t <= max; }

    static const interval empty;
    static const interval universe;
};
