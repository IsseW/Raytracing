#include "catch.h"

#include <iostream>
#include <array>
#include <string>
#include <cmath>

#include "TestHelper.h"
#include "Ray.h"
#include "Plane.h"

struct PlaneTestData
{
    std::array<Vector3D, 3> planeData;
    std::array<Vector3D, 2> rayData;
    bool hits;
    double distance;
};

SCENARIO("A Plane can be created and used for correct intersection testing with rays", "[Plane]")
{
    typedef Vector3D Vec3;
    // Plane: colour, point on plane, normal of plane
    // Ray: origin, direction'
    std::vector<PlaneTestData> testData =
    {
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 10.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 20.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, 1.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(-10.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(1.0, 0.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(-1.0, 0.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, 1.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, -10.0), Vec3(0.0, -1.0, 0.0)}, false, 0.0},

        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(15.0, -5.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0)}, true, 15.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(15.0, 0.0, 12.34), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0)}, true, 15.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(5.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0)}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(10.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 10.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(-5.0, 15.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 15.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 15.0, 12.34), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 15.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 5.0, 0.0), Vec3(0.0, 1.0, 0.0)}, true, 5.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, -1.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(-1.0, 0.0, 0.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0)}, false, 0.0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 10.0, 0.0), Vec3(0.0, -1.0, 0.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, -1.0)}, false, 0.0},

        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.707106, 0.707106)}, true, sqrt(2)},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, -0.707106, 0.707106)}, true, sqrt(2)},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.707106, 0.0, 0.707106)}, true, sqrt(2)},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(-0.707106, 0.0, 0.707106)}, true, sqrt(2)},

        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.707106, -0.707106)}, false, 0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.0, -0.707106, -0.707106)}, false, 0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(0.707106, 0.0, -0.707106)}, false, 0},
        {{Vec3(0.0, 0.0, 0.0), Vec3(0.0, 0.0, 1.0), Vec3(0.0, 0.0, -1.0)}, {Vec3(0.0, 0.0, 0.0), Vec3(-0.707106, 0.0, -0.707106)}, false, 0},
    };

    WHEN("A Plane object is created and intersection tests are performed with rays")
    {
        THEN("The intersection function should correctly indicate if the ray hits the plane, and if hits, at what distance")
        {
            for (auto& input : testData)
            {
                auto& planeData = input.planeData;
                auto& rayData = input.rayData;
                Plane plane(planeData[0], planeData[1], planeData[2]);
                Ray ray(rayData[0], rayData[1]);
                bool resultingHit = false;
                double resultingDistance = 0.0;
                resultingHit = plane.Intersection(ray, resultingDistance);

                std::string info = "Plane: point on plane(" + ToString(planeData[1]) + "), normal of plane(" + ToString(planeData[2]) + ")";
                info += "\nRay: origin(" + ToString(rayData[0]) + "), direction(" + ToString(rayData[1]) + ")";
                info += "\nExpected to hit: " + std::string(input.hits == true ? "yes" : "no");
                info += input.hits == true ? ("\nExpected distance to hit: " + std::to_string(input.distance)) : "";
                info += "\nResulted in hit: " + std::string(resultingHit == true ? "yes" : "no");
                info += resultingHit == true ? ("\nResulting distance to hit: " + std::to_string(resultingDistance)) : "";

                INFO(info);
                REQUIRE(resultingHit == input.hits);
                if(input.hits)
                    REQUIRE(ApproximatelyEqual(resultingDistance, input.distance));

            }
        }
    }
}