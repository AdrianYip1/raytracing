#include <iostream>

int main() {
	// Image
	int imageW = 256;
	int imageH = 256;

	// Render
	std::cout << "P3\n" << imageW << ' ' << imageH << "\n255\n";

	for (int j = 0; j < imageH; j++) {
		for (int i = 0; i < imageW; i++) {
			auto r = double(i) / (imageW - 1);
			auto g = double(j) / (imageH - 1);
			auto b = 0.0;

			int ir = int(255.999 * r);
			int ig = int(255.999 * g);
			int ib = int(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << ' ' << '\n';
		}
	}
	return 0;
}
