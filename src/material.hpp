#pragma once

#include "hittable.hpp"
#include "utilities.hpp"

class material {
	public:
		virtual ~material() = default;

		virtual bool scatter(const Ray& r_in, 
						 	 const hit_record& rec, 
							 color& attenuation, 
							 Ray& scattered) const;
	private:
};

class lambertian : public material {
	public:
		lambertian(const color& albedo);

		bool scatter(const Ray& r_in,
			const hit_record& rec,
			color& attenuation,
			Ray& scattered) const override;

	private:
		color albedo;
};

class metal : public material {
	public:
		metal(const color& albedo, float fuzz);

		bool scatter(const Ray& r_in,
			const hit_record& rec,
			color& attenuation,
			Ray& scattered) const override;

	private:
		color albedo;
		float fuzz;
};