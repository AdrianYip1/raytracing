#pragma once

#include "hittable.hpp"
#include "enginemath/vec3.hpp"

class sphere : public hittable {
	public:
		sphere(const enginemath::Vec3& _center, float _radius);

		bool hit(const Ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const override;
	private:
		enginemath::Vec3 center;
		float radius;
};