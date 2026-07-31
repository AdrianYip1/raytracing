#include <iostream>
#include <cstdlib>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"
#include <enginemath/vec3.hpp>

#include "color.hpp"

int main() {
	// Image
	int imageW = 256;
	int imageH = 256;
	std::vector<unsigned char> data;
	data.reserve(imageW * imageH * 3);

	// Render
	for (int j = 0; j < imageH; j++) {
		std::clog << "\rScanlines remaining: " << (imageH - j) << " " << std::flush;
		for (int i = 0; i < imageW; i++) {
			auto pixel_color = color(double(i) / (imageW - 1), double(j) / (imageH - 1), 0.0);
			writeColor(data, pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";

	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
	system("start image.png");
	return 0;
}
