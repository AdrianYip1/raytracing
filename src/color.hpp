#pragma once

#include <enginemath/vec3.hpp>
#include <vector>

using color = enginemath::Vec3;

void writeColor(std::vector<unsigned char>& data, const color& pixel_color);