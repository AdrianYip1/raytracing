#pragma once
#include <enginemath/vec3.hpp>
#include "defines.h"

namespace enginemath {
	static enginemath::Vec3 random() {
		return enginemath::Vec3(random_float(), random_float(), random_float());
	}

	static enginemath::Vec3 random(float min, float max) {
		return enginemath::Vec3(random_float(min, max), random_float(min, max), random_float(min, max));
	}

	inline enginemath::Vec3 random_unit_vector() {
		while (true) {
			auto p = random(-1, 1);
			auto lensq = p.magnitudeSq();
			if (1e-30f < lensq && lensq <= 1.0f) { // meaning inside the sphere
				return p.normalized();
			}
		}
	}

	inline enginemath::Vec3 random_on_hemisphere(enginemath::Vec3 normal) {
		enginemath::Vec3 on_unit_sphere = random_unit_vector();
		if (on_unit_sphere.dot(normal) > 0.0) {
			return on_unit_sphere;
		}
		else {
			return -on_unit_sphere;
		}
	}

	inline enginemath::Vec3 refract(const enginemath::Vec3& uv, const enginemath::Vec3& n, double etai_over_etat) {
		auto cos_theta = std::fmin((-uv).dot(n), 1.0);

		enginemath::Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
		enginemath::Vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.magnitudeSq())) * n;
		return r_out_perp + r_out_parallel;
	}
}