#pragma once

class interval {
	public:
		float min, max;

		interval();

		interval(float min, float max);

		float size() const;

		bool contains(float x) const;

		bool surrounds(float x) const;

		static const interval empty, universe;
};
