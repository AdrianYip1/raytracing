#include "sphere.hpp"

sphere::sphere(const enginemath::Vec3& _center, float _radius) :
	center(_center), radius(_radius) {

}

bool sphere::hit(const Ray& r, float ray_tmin, float ray_tmax, hit_record& rec) const {
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
	if (root <= ray_tmin || root >= ray_tmax) {
		root = (h + sqrtD) / a;
		if (root <= ray_tmin || root >= ray_tmax) {
			return false;
		}
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	// Normalize for cheaper since length of rec.p - center is radius
	rec.normal = (rec.p - center) / radius;

	return true;
}