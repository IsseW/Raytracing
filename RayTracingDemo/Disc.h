#pragma once

#include "Shape.h"
#include "Vector3D.h"
#include "Ray.h"

class Disc : public Shape
{
private:
	Vector3D centerPoint;
	Vector3D normal;
	double radius;

public:
	Disc(const Vector3D& colour, const Vector3D& c, const Vector3D& n, double r);

	bool Intersection(const Ray& ray, double& t) override;

};