#include "horizon/interval.h"
#include <limits>

const interval interval::empty    = interval(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const interval interval::universe = interval(-std::numeric_limits<double>::infinity(),  std::numeric_limits<double>::infinity());
