#include "Sphere.h"

#include <cmath>

Sphere::Sphere(const Vector3D & colour, const Vector3D c, double r) : Shape(colour), center(c), radius(r) { }

bool Sphere::Intersection(const Ray & ray, double & t)
{
	Vector3D localPoint = this->center - ray.origin;
	double relative_distance = localPoint * ray.direction;
	double distanceToCenterSqr = localPoint * localPoint;
	if (relative_distance < 0 && distanceToCenterSqr > radius * radius) return false;
	double msqr = distanceToCenterSqr - relative_distance * relative_distance;
	if (msqr > radius * radius) return false;
	double q = std::sqrt(radius * radius - msqr);
	if (distanceToCenterSqr > radius * radius) t = relative_distance - q;
	else t = relative_distance + q;
	return true;
}