#include "Ray.h"

Ray::Ray(const Vector3D& o, const Vector3D& d) :
	origin(o), direction(d)
{
	direction.Normalize();
}