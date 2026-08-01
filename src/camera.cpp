#include "camera.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"

void camera::render(const hittable& world) {
	initalize();
	for (int j = 0; j < imageH; j++) {
		std::clog << "\rScanlines remaining: " << (imageH - j) << " " << std::flush;
		for (int i = 0; i < imageW; i++) {
			auto pixelCenter = pixel00_loc + (j * pixelDv) + (i * pixelDu);
			auto rayDirection = pixelCenter - camera_center;
			Ray r(camera_center, rayDirection);

			color pixel_color = ray_color(r, world);
			writeColor(data, pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";
	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
}

void camera::initalize() {
	imageH = int(imageW / aspect_ratio);
	imageH = std::max(imageH, 1);

	camera_center = enginemath::Vec3(0.0, 0.0, 0.0);

	// viewport
	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (float(imageW) / imageH);

	// vectors across the viewport's x and y direction
	auto viewportU = enginemath::Vec3(viewport_width, 0.0, 0.0);
	auto viewportV = enginemath::Vec3(0.0, -viewport_height, 0.0);

	pixelDu = viewportU / imageW;
	pixelDv = viewportV / imageH;

	auto viewport_upper_left = camera_center - enginemath::Vec3(0.0, 0.0, focal_length) - 0.5 * (viewportU + viewportV);
	pixel00_loc = viewport_upper_left + 0.5 * (pixelDu + pixelDv);

	data.reserve(imageW * imageH * 3);
}

color camera::ray_color(const Ray& r, const hittable& world) const {
	hit_record rec;

	if (world.hit(r, interval(0, infinity), rec)) {
		return 0.5 * (rec.normal + enginemath::Vec3(1.0, 1.0, 1.0));
	}

	enginemath::Vec3 unitDir = r.getDirection().normalized();
	auto a = 0.5 * (unitDir.y + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}