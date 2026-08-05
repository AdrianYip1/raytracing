#pragma once

#include <enginemath/vec3.hpp>
#include <vector>
#include "interval.hpp"

using color = enginemath::Vec3;

inline float linear_to_gamma(float linear);

void writeColor(std::vector<unsigned char>& data, const color& pixel_color);