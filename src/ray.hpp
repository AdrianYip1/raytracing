#pragma once
#include <enginemath/vec3.hpp>

class Ray {
	public:
		Ray();

		Ray(const enginemath::Vec3& _origin, 
			const enginemath::Vec3& _direction);
		
		const enginemath::Vec3& getOrigin() const { return origin; };
		const enginemath::Vec3& getDirection() const { return direction; };

		enginemath::Vec3 at(double t) const;
	private:
		enginemath::Vec3 origin;
		enginemath::Vec3 direction;
};
