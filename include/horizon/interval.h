#pragma once

struct interval {
    double min;
    double max;

    interval() : min(0.0), max(0.0) {}
    interval(double min_val, double max_val) : min(min_val), max(max_val) {}

    bool surrounds(double t) const {
        return t >= min && t <= max;
    }
};
