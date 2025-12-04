#pragma once

#include <string>

namespace app {

class Example {
public:
    Example();
    Example(const std::string& name, int value);

    void set_value(int v);
    int get_value() const;

    void greet() const;

private:
    std::string name_;
    int value_;
};

} // namespace myproject
