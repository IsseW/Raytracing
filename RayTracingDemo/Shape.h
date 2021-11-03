#pragma once

#include "Vector3D.h"
#include "Ray.h"
constexpr double EPS = 1e-7;

class Shape
{
private:

protected:
	Vector3D colour;

public:
	// colour: Shape colour
	Shape(const Vector3D& colour);

	const Vector3D& GetColour();

	// ray: A ray that should be used for intersection testing with the shape
	// t: A reference value that is to be set to the distance from the ray origin at which the intersection occurs, if it occurs (can be ignored if no intersection)
	virtual bool Intersection(const Ray& ray, double& t) = 0;

};