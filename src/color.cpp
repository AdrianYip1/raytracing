#include "color.hpp"


void writeColor(std::vector<unsigned char>& data, const color& pixel_color) {
	auto r = pixel_color.x;
	auto g = pixel_color.y;
	auto b = pixel_color.z;

	static const interval intensity(0.000, 0.999);
	int ir = int(255.999 * intensity.clamp(r));
	int ig = int(255.999 * intensity.clamp(g));
	int ib = int(255.999 * intensity.clamp(b));

	data.push_back(static_cast<unsigned char>(ir));
	data.push_back(static_cast<unsigned char>(ig));
	data.push_back(static_cast<unsigned char>(ib));
}