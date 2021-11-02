#include "Triangle.h"
#include <cmath>

constexpr double EPS = 0.000001;


Triangle::Triangle(const Vector3D & colour, const Vector3D & p0, const Vector3D & p1, const Vector3D & p2) : Shape(colour), p0(p0), p1(p1), p2(p2) { }

bool Triangle::Intersection(const Ray & ray, double & t)
{
	//	(p2)
	//	 ^ e2
	//	 |
	//	 |		 e1
	//	(p0)------>(p1)
	Vector3D e1 = this->p1 - this->p0;
	Vector3D e2 = this->p2 - this->p0;
	Vector3D q = ray.direction ^ e2;
	double a = e1 * q;
	if (std::abs(a) < EPS) return false;
	double f = 1 / a;
	Vector3D s = ray.origin - this->p0;
	double u = f * (s * q);
	if (u < 0.0) return false;
	Vector3D r = s ^ e1;
	double v = f * (ray.direction * r);
	if (v < 0.0 || u + v > 1.0) return false;
	t = f * (e2 * r);
	return t > 0.0;
}
