#include "Plane.h"
#include <cmath>

Plane::Plane(const Vector3D & colour, const Vector3D & p, const Vector3D & n) : Shape(colour), normal(n)
{
	this->distance = -(p * n);
}

bool Plane::Intersection(const Ray & ray, double & t)
{
	double e = this->normal * ray.direction;

	// Check if the ray is parallell with the plane
	if (std::abs(e) < EPS) 
	{
		// Check if the ray origin is on the plance
		if (std::abs(this->normal * ray.origin + this->distance) < EPS)
		{
			t = 0.0;
			return true;
		}
		else 
		{
			return false;
		}
	}
	t = (-this->distance - (this->normal * ray.origin)) / e;
	return t >= 0.0;
}
