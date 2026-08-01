#pragma once

#include "defines.h"

class hit_record {
	public:
		enginemath::Vec3 p;
		enginemath::Vec3 normal;
		float t;
		bool front_face;

		void set_face_normal(const Ray& r, const enginemath::Vec3& outward_normal);
};

class hittable {
	public:
		virtual ~hittable() = default;

		virtual bool hit(const Ray& r, interval ray_t, hit_record& rec) const = 0;
};