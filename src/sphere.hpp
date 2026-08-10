#pragma once

#include "hittable.hpp"

#include "defines.h"

class sphere : public hittable {
	public:
		sphere(const enginemath::Vec3& _center, float _radius, std::shared_ptr<material> _mat);

		bool hit(const Ray& r, interval ray_t, hit_record& rec) const override;
	private:
		enginemath::Vec3 center;
		float radius;
		std::shared_ptr<material> mat;
};