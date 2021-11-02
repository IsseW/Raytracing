#include "catch.h"

#include <iostream>
#include <array>
#include <string>
#include <cmath>

#include "TestHelper.h"
#include "Ray.h"
#include "Sphere.h"

struct SphereData
{
    Vector3D colour;
    Vector3D centerPoint;
    double radius;
};

struct SphereTestData
{
    SphereData sphereData;
    std::array<Vector3D, 2> rayData;
    bool hits;
    double distance;
};

SCENARIO("A Sphere can be created and used for correct intersection testing with rays", "[Sphere]")
{
    typedef Vector3D Vec3;
    // Sphere: colour, center, radius
    // Ray: origin, direction'
    std::vector<SphereTestData> testData =
    {
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 5.0), 5.0}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 0.0, -15.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-5.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 5.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -5.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},

        // Edges of sphere
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), 5.0 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), 5.0 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), 5.0 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), 5.0 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), 5.0}, {Vec3(5.0 * sqrt(0.5), 5.0 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 11.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), 5.0 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 12.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 3.0), 5.0}, {Vec3(5.0 * sqrt(0.5), 5.0 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 13.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 4.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), 5.0 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 14.0},

        // All of the calculations are to find where the 45 degree rotated points are
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3((5 - 5 * sqrt(0.5)) / tan(0.392699), 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-(5 - 5 * sqrt(0.5)) / tan(0.392699), 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -(5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0), Vec3(0.0, 0.0, 1.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},



        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 5.0, 0.0), 5.0}, {Vec3(0.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -15.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-5.0, -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -10.0, 5.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -10.0, -5.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},

        // Edges of sphere
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), -10.0, 5.0 * sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), -10.0, 5.0 * sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), -10.0, 5.0 * -sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), -10.0, 5.0 * -sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), -10.0, 5.0 * sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 11.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 2.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), -10.0, 5.0 * sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 12.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 3.0, 0.0), 5.0}, {Vec3(5.0 * sqrt(0.5), -10.0, 5.0 * -sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 13.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 4.0, 0.0), 5.0}, {Vec3(5.0 * -sqrt(0.5), -10.0, 5.0 * -sqrt(0.5)), Vec3(0.0, 1.0, 0.0)}, true, 14.0},

        // All of the calculations are to find where the 45 degree rotated points are
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3((5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-(5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -10.0, (5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -10.0, -(5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, -sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699), -10.0, -sqrt(0.5) * (5 - 5 * sqrt(0.5)) / tan(0.392699)), Vec3(0.0, 1.0, 0.0)}, true, 5.0 + (5 - 5.0 * sqrt(0.5))},
    


        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 0.0, 10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 0.0, 10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, -sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 0.0, -10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 0.0, -10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 2.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 2.0, 10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 3.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 3.0, 10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, -sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 4.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 4.0, -10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, sqrt(0.5))}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 5.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 5.0, -10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, sqrt(0.5))}, true, 5.0},



        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 5.0), 5.0}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 0.0, -15.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-5.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, 5.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(0.0, -5.0, -10.0), Vec3(0.0, 0.0, 1.0) * -1}, false, 0.0},

        // Just outside the edges of the sphere
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.1 * sqrt(0.5), 5.1 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.1 * -sqrt(0.5), 5.1 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.1 * sqrt(0.5), 5.1 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(5.1 * -sqrt(0.5), 5.1 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), 5.0}, {Vec3(5.1 * sqrt(0.5), 5.1 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 2.0), 5.0}, {Vec3(5.1 * -sqrt(0.5), 5.1 * sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 3.0), 5.0}, {Vec3(5.1 * sqrt(0.5), 5.1 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 4.0), 5.0}, {Vec3(5.1 * -sqrt(0.5), 5.1 * -sqrt(0.5), -10.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},

        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 0.0, 10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 0.0, 10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, -sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 0.0, -10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 0.0, -10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 2.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 2.0, 10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, -sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 3.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 3.0, 10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, -sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 4.0, 0.0), 5.0}, {Vec3(10.0 * sqrt(0.5), 4.0, -10.0 * sqrt(0.5)), Vec3(-sqrt(0.5), 0.0, sqrt(0.5)) * -1}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 5.0, 0.0), 5.0}, {Vec3(-10.0 * sqrt(0.5), 5.0, -10.0 * sqrt(0.5)), Vec3(sqrt(0.5), 0.0, sqrt(0.5)) * -1}, false, 0.0},
    };

    WHEN("A Sphere object is created and intersection tests are performed with rays")
    {
        THEN("The intersection function should correctly indicate if the ray hits the plane, and if hits, at what distance")
        {
            for (auto& input : testData)
            {
                auto& sphereData = input.sphereData;
                auto& rayData = input.rayData;
                Sphere sphere(sphereData.colour, sphereData.centerPoint, sphereData.radius);
                Ray ray(rayData[0], rayData[1]);
                bool resultingHit = false;
                double resultingDistance = 0.0;
                resultingHit = sphere.Intersection(ray, resultingDistance);

                std::string info = "Sphere: Center point(" + ToString(sphereData.centerPoint) + "), radius(" + std::to_string(sphereData.radius) + ")";
                info += "\nRay: origin(" + ToString(rayData[0]) + "), direction(" + ToString(rayData[1]) + ")";
                info += "\nExpected to hit: " + std::string(input.hits == true ? "yes" : "no");
                info += input.hits == true ? ("\nExpected distance to hit: " + std::to_string(input.distance)) : "";
                info += "\nResulted in hit: " + std::string(resultingHit == true ? "yes" : "no");
                info += resultingHit == true ? ("\nResulting distance to hit: " + std::to_string(resultingDistance)) : "";

                INFO(info);
                REQUIRE(resultingHit == input.hits);
                if (input.hits)
                    REQUIRE(ApproximatelyEqual(resultingDistance, input.distance));

            }
        }
    }
}