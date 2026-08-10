#include "sphere.hpp"

sphere::sphere(const enginemath::Vec3& _center, float _radius, std::shared_ptr <material> _mat) :
	center(_center), radius(std::fmax(0, _radius)), mat(_mat) {

}

bool sphere::hit(const Ray& r, interval ray_t, hit_record& rec) const {
	enginemath::Vec3 oc = center - r.getOrigin();
	auto a = r.getDirection().dot(r.getDirection());
	auto h = r.getDirection().dot(oc);
	auto c = (oc).dot(oc) - radius * radius;

	auto discrim = h * h - a * c;
	if (discrim < 0) return false;

	// Find nearest root that lies in the accepted range
	auto sqrtD = std::sqrt(discrim);
	// Check the near hit first
	auto root = (h - sqrtD) / a;
	if (!ray_t.surrounds(root)) {
		root = (h + sqrtD) / a;
		if (!ray_t.surrounds(root)) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	enginemath::Vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat = mat;

	return true;
}