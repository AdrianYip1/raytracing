#include "material.hpp"


bool material::scatter(const Ray& r_in,
	const hit_record& rec,
	color& attenuation,
	Ray& scattered) const {
	return false;
}

lambertian::lambertian(const color& albedo) : albedo(albedo) {

}

bool lambertian::scatter(const Ray& r_in,
	const hit_record& rec,
	color& attenuation,
	Ray& scattered) const {

	auto scatter_direction = rec.normal + enginemath::random_unit_vector();

	if (scatter_direction.basicallyZero()) {
		scatter_direction = rec.normal;
	}
	scattered = Ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}

metal::metal(const color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {

}

bool metal::scatter(const Ray& r_in,
	const hit_record& rec,
	color& attenuation,
	Ray& scattered) const {

	enginemath::Vec3 reflected = r_in.getDirection().reflectAcross(rec.normal);

	reflected = reflected.normalized() + (fuzz * enginemath::random_unit_vector());
	scattered = Ray(rec.p, reflected);
	attenuation = albedo;
	return (scattered.getDirection().dot(rec.normal) > 0);
}