#include "app/example.h"
#include <iostream>

namespace app {

Example::Example()
    : name_("Unnamed"), value_(0)
{}

Example::Example(const std::string& name, int value)
    : name_(name), value_(value)
{}

void Example::set_value(int v) {
    value_ = v;
}

int Example::get_value() const {
    return value_;
}

void Example::greet() const {
    std::cout << "Hello from " << name_
              << "! Current value = " << value_ << "\n";
}

} // namespace myproject
