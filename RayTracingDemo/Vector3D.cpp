#include "Vector3D.h"
#include <cmath>

Vector3D::Vector3D(double xValue, double yValue, double zValue) : x(xValue), y(yValue), z(zValue) { }

Vector3D Vector3D::operator+(const Vector3D& right) const
{
	return Vector3D(this->x + right.x, this->y + right.y, this->z + right.z);
}

Vector3D Vector3D::operator-(const Vector3D& right) const
{
	return Vector3D(this->x - right.x, this->y - right.y, this->z - right.z);
}

double Vector3D::operator*(const Vector3D& right) const
{
	return this->x * right.x + this->y * right.y + this->z * right.z;
}

Vector3D Vector3D::operator^(const Vector3D& right) const
{
	return Vector3D(this->GetY() * right.GetZ() -  this->GetZ() * right.GetY(), 
					-this->GetX() * right.GetZ() + this->GetZ() * right.GetX(), 
					this->GetX() * right.GetY() - this->GetY() * right.GetX());
}

Vector3D Vector3D::operator*(double scalar) const
{
	return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

double Vector3D::GetX() const
{
	return this->x;
}

double Vector3D::GetY() const
{
	return this->y;
}

double Vector3D::GetZ() const
{
	return this->z;
}

double Vector3D::Length() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

void Vector3D::Normalize()
{
	double len = this->Length();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}
