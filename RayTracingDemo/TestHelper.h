#pragma once

#include <cmath>
#include <string>
#include <array>

#include "Vector3D.h"

inline bool ApproximatelyEqual(double value1, double value2, double delta = 0.001)
{
    return abs(value1 - value2) <= delta;
}

inline std::string ToString(const Vector3D& vector)
{
    std::string toReturn = "x = " + std::to_string(vector.GetX());
    toReturn += ", y = " + std::to_string(vector.GetY());
    toReturn += ", z = " + std::to_string(vector.GetZ());

    return toReturn;
}

inline std::string ToString(const std::array<double, 3>& array)
{
    std::string toReturn = "x = " + std::to_string(array[0]);
    toReturn += ", y = " + std::to_string(array[1]);
    toReturn += ", z = " + std::to_string(array[2]);

    return toReturn;
}