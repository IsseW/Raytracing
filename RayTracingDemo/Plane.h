#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Ray.h"

class Plane : public Shape
{
private:
	// Add member variables and helper functions as you see fit

public:
	// colour: Shape colour
	// pointOnPlane: A point that lies in the plane
	// normalOfPlane: The normal vector of the plane
	Plane(const Vector3D& colour, const Vector3D& pointOnPlane, const Vector3D& normalOfPlane);

	bool Intersection(const Ray& ray, double& t) override;
};