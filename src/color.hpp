#pragma once

#include <enginemath/vec3.hpp>
#include <vector>
#include "interval.hpp"

using color = enginemath::Vec3;

void writeColor(std::vector<unsigned char>& data, const color& pixel_color);