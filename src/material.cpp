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

dielectric::dielectric(float refraction_index) : refraction_index(refraction_index) {

}

bool dielectric::scatter(const Ray& r_in,
	const hit_record& rec,
	color& attenuation,
	Ray& scattered) const {

	attenuation = color(1.0f);
	double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

	enginemath::Vec3 unit_direction = r_in.getDirection().normalized();
	float cos_theta = std::fmin((-unit_direction).dot(rec.normal), 0);
	float sin_theta = std::sqrt(1 - cos_theta * cos_theta);
	enginemath::Vec3 direction;

	// check for TIR
	if (ri * sin_theta > 1.0) {
		direction = unit_direction.reflectAcross(rec.normal);
	}
	else {
		direction = enginemath::refract(unit_direction, rec.normal, ri);
	}
	

	scattered = Ray(rec.p, direction);
	return true;
}