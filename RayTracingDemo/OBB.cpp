#include "OBB.h"
#include <cmath>
#include <limits>
#include <tuple>
OBB::OBB(const Vector3D& colour, const Vector3D& centerPoint, const Vector3D& u, const Vector3D& v, const Vector3D& w,
	double width, double height, double depth) : Shape(colour), centerPoint(centerPoint), u(u), v(v), w(w), size(width, height, depth)
{
	this->u.Normalize();
	this->v.Normalize();
	this->w.Normalize();
}

bool OBB::Intersection(const Ray& ray, double& t)
{
	double tmin = -std::numeric_limits<double>::infinity();
	double tmax = std::numeric_limits<double>::infinity();

	Vector3D localPoint = this->centerPoint - ray.origin;

	for (std::tuple<Vector3D, double> tp : 
			{ 
				std::make_tuple(this->u, this->size.GetX()), 
				std::make_tuple(this->v, this->size.GetY()), 
				std::make_tuple(this->w, this->size.GetZ()) 
			})
	{
		Vector3D direction = std::get<Vector3D>(tp);
		double size = std::get<double>(tp);

		double e = direction * localPoint;
		double f = direction * ray.direction;

		if (std::abs(f) > EPS) {
			double t0 = (e + size) / f;
			double t1 = (e - size) / f;
			if (t0 > t1) std::swap(t0, t1);
			if (t0 > tmin) tmin = t0;
			if (t1 < tmax) tmax = t1;
			if (tmin > tmax || tmax < 0) return false;
		}
		else if (-e + size < 0.0 || -e - size > 0.0) return false;
	}
	if (tmin > 0) {
		t = tmin;
	}
	else {
		t = tmax;
	}
	return true;
}
