#include "ray.hpp"

Ray::Ray() {

}

Ray::Ray(const enginemath::Vec3& _origin, 
		 const enginemath::Vec3& _direction) :
	origin(_origin), direction(_direction) {

}


enginemath::Vec3 Ray::at(double t) const {
	return origin + t * direction;
}