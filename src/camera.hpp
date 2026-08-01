#pragma once
#include "hittable.hpp"

class camera {
	public:
		double aspect_ratio = 1.0;
		int imageW = 100;

		void render(const hittable& world);

	private:
		int imageH;
		enginemath::Vec3 camera_center;
		enginemath::Vec3 pixel00_loc;
		enginemath::Vec3 pixelDv;
		enginemath::Vec3 pixelDu;
		std::vector<unsigned char> data;

		void initalize();
		color ray_color(const Ray& r, const hittable& world) const;
};