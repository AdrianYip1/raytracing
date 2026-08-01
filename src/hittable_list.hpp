#pragma once

#include "hittable.hpp"

#include "defines.h"
#include <vector>


class hittable_list : public hittable {
	public:
		std::vector<std::shared_ptr<hittable>> objects;

		hittable_list() {}

		hittable_list(std::shared_ptr<hittable> object);

		void add(std::shared_ptr<hittable> object);

		bool hit(const Ray& r, interval ray_t, hit_record& rec) const override;
};