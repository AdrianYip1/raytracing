#include "hittable.hpp"

void hit_record::set_face_normal(const Ray& r, const enginemath::Vec3& outward_normal) {
	// Sets the hit record normal vector
	//outward normal should be unit length

	// if the dot between the ray and normal > 0 its inside the object
	front_face = (r.getDirection().dot(outward_normal) > 0.0);
	normal = front_face ? outward_normal : -outward_normal;
}