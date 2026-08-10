#include "camera.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vendor/stb_image_write.h"
#include "utilities.hpp"

void camera::render(const hittable& world) {
	initalize();
	for (int j = 0; j < imageH; j++) {
		std::clog << "\rScanlines remaining: " << (imageH - j) << " " << std::flush;
		for (int i = 0; i < imageW; i++) {
			color pixel_color(0.0, 0.0, 0.0);
			for (int sample = 0; sample < samples_per_pixel; sample++) {
				Ray r = get_ray(i, j);
				pixel_color += ray_color(r, max_depth, world);
			}
			writeColor(data, pixel_samples_scale * pixel_color);
		}
	}
	std::clog << "\rDone.                 \n";
	stbi_write_png("image.png", imageW, imageH, 3, data.data(), imageW * 3);
}

void camera::initalize() {
	pixel_samples_scale = 1.0 / samples_per_pixel;

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

color camera::ray_color(const Ray& r, int depth, const hittable& world) const {
	if (depth <= 0) return color(0.0, 0.0, 0.0);

	hit_record rec;

	if (world.hit(r, interval(0.001, infinity), rec)) {
		Ray scattered;
		color attenuation;
		if (rec.mat->scatter(r, rec, attenuation, scattered)) {
			return attenuation * ray_color(scattered, depth - 1, world);
		}
		return color(0.0f, 0.0f, 0.0f);
	}

	enginemath::Vec3 unitDir = r.getDirection().normalized();
	auto a = 0.5 * (unitDir.y + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

Ray camera::get_ray(int i, int j) const {
	// construct a camera ray from he origin directed at randomly sampled points
	// from i, j
	auto offset = sample_square(); 
	auto pixel_sample = pixel00_loc +
						((i + offset.x) * pixelDu) +
						((j + offset.y) * pixelDv);

	auto ray_origin = camera_center;
	auto ray_direction = pixel_sample - ray_origin;

	return Ray(ray_origin, ray_direction);
}

enginemath::Vec3 camera::sample_square() const {
	return enginemath::Vec3(random_float() - 0.5, random_float() - 0.5, 0);
}