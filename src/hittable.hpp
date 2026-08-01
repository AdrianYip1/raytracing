#pragma once

#include "ray.hpp"
#include "enginemath/vec3.hpp"

class hit_record {
	public:
		enginemath::Vec3 p;
		enginemath::Vec3 normal;
		float t;
};

class hittable {
	public:
		virtual ~hittable() = default;

		virtual bool hit(const Ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const = 0;
};