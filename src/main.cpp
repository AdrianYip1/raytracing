#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"
#include <cstdlib>
#include <vector>

int main() {
	// Image
	int imageW = 256;
	int imageH = 256;
	std::vector<unsigned char> data;
	data.reserve(imageW * imageH * 3);

	// Render
	for (int j = 0; j < imageH; j++) {
		for (int i = 0; i < imageW; i++) {
			auto r = double(i) / (imageW - 1);
			auto g = double(j) / (imageH - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			data.push_back(static_cast<unsigned char>(ir));
			data.push_back(static_cast<unsigned char>(ig));
			data.push_back(static_cast<unsigned char>(ib));
		}
	}

	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
	system("start image.png");
	return 0;
}
