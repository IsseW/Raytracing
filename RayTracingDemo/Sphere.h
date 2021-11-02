#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Ray.h"

class Sphere : public Shape
{
private:
	// Add member variables and helper functions as you see fit
	Vector3D center;
	double radius;

public:
	// colour: Shape colour
	// centerPoint: Point at which the sphere center lies
	// radius: The radius of the sphere
	Sphere(const Vector3D& colour, const Vector3D centerPoint, double radius);

	bool Intersection(const Ray& ray, double& t) override;
};