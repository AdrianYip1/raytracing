#pragma once
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_float() {
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_float(float min, float max) {
    return min + (max - min) * random_float();
}
// Common Headers

#include "color.hpp"
#include "Ray.hpp"
#include "interval.hpp"
#include "enginemath/vec3.hpp"