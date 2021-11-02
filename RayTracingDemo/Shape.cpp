#include "Shape.h"

Shape::Shape(const Vector3D & colour) : colour(colour)
{
	//EMPTY
}

const Vector3D & Shape::GetColour()
{
	return colour;
}
