#include "Disc.h"

Disc::Disc(const Vector3D& colour, const Vector3D& c, const Vector3D& n, double r) :
	Shape(colour), centerPoint(c), normal(n), radius(r)
{
	normal.Normalize();
}

// P = Intersection point
// C = Centerpoint
// N = Normal

// (P - C) * N = (Px - Cx) * Nx + (Py - Cy) * Ny + (Pz - Cz) * Nz =>
// Px*Nx - Cx*Nx + Py*Ny - Cy*Ny + Pz*Nz - Cz*Nz =>
// Px*Nx + Py*Ny + Pz*Nz = Cx*Nx + Cy*Ny + Cz*Nz

// P = O + D*t = (Ox + Dx*t, Oy + Dy*t, Oz + Dz*t)

// Ox*Nx + Dx*t*Nx + Oy*Ny + Dy*t*Ny + Oz*Nz + Dz*t*Nz = Cx*Nx + Cy*Ny + Cz*Nz =>
// Dx*t*Nx + Dy*t*Ny + Dz*t*Nz = Cx*Nx + Cy*Ny + Cz*Nz - Ox*Nx - Oy*Ny - Oz*Nz =>
// t*(Dx*Nx + Dy*Ny + Dz*Nz) = Cx*Nx + Cy*Ny + Cz*Nz - Ox*Nx - Oy*Ny - Oz*Nz =>
// t = (Cx*Nx + Cy*Ny + Cz*Nz - Ox*Nx - Oy*Ny - Oz*Nz) / (Dx*Nx + Dy*Ny + Dz*Nz) =>
// t = (C * N - O * N) / (D * N) = (C - O) * N / (D * N)

bool Disc::Intersection(const Ray & ray, double & t)
{
	Vector3D origin = ray.origin;
	Vector3D direction = ray.direction;

	// Check if ray is perpendicular to, or away from, disc
	double directionDotNormal = direction * normal;
	if (directionDotNormal > 0.0f)
		return false;

	Vector3D originToCenter = centerPoint - origin;
	double originToCenterDotNormal = originToCenter * normal;
	t = originToCenterDotNormal / directionDotNormal;

	if (t < 0.0f)
		return false;

	Vector3D intersectionPoint = origin + direction * t;
	double distanceToCenter = (intersectionPoint - centerPoint).Length();

	return distanceToCenter <= radius;
}