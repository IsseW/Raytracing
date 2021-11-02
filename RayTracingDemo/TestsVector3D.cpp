#define CATCH_CONFIG_MAIN
#include "catch.h"

#include <iostream>
#include <array>
#include <string>
#include <utility>

#include "TestHelper.h"
#include "Vector3D.h"


SCENARIO("A Vector3D can be created and its components retrieved", "[Vector3D]")
{
    std::vector<std::array<double, 3>> inputComponents =
    {
        {0.0, 0.0, 0.0}, {1.0, 2.0, 3.0}, {-1.3, 3.7, 4.2},
        {-0.0, -1.3, -3.1}, {10.0, 9.0, 8.0}, {33.3, 22.2, 11.1}
    };

    WHEN("The Vector3D object is created with direction values")
    {
        THEN("All components of the object should be as expected when get functions are called")
        {
            for (auto& input : inputComponents)
            {
                Vector3D testObject(input[0], input[1], input[2]);

                std::string info = "Expected values: " + ToString(input);
                info += "\nActual values: " + ToString(testObject);

                INFO(info);
                REQUIRE(testObject.GetX() == input[0]);
                REQUIRE(testObject.GetY() == input[1]);
                REQUIRE(testObject.GetZ() == input[2]);
            }
        }
    }
}

struct TestOperatorData
{
    std::array<double, 3> vec1;
    std::array<double, 3> vec2;
    std::array<double, 3> result;
};

SCENARIO("A Vector3D can be added to another Vector3D and the resulting object contains mathematically correct values", "[Vector3D]")
{
    std::vector<TestOperatorData> testData =
    {
        {{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {2.0, 4.0, 6.0}},
        {{0.0, 0.0, 0.0}, {1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}},
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -2.0, -3.0}, {1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}},
        {{-2.0, -4.0, -8.0}, {-1.0, -1.0, -1.0}, {-3.0, -5.0, -9.0}},
        {{-2.5, -4.5, -8.5}, {-1.4, -1.4, -1.4}, {-3.9, -5.9, -9.9}}
    };

    WHEN("A Vector3D object is added to another using operator+")
    {
        THEN("All components of the resulting object should be as expected when get functions are called")
        {
            for (auto& input : testData)
            {
                Vector3D testObject1(input.vec1[0], input.vec1[1], input.vec1[2]);
                Vector3D testObject2(input.vec2[0], input.vec2[1], input.vec2[2]);
                Vector3D testResult = testObject1 + testObject2;

                std::string info = "Vector3D object 1 components: x = " + ToString(testObject1);
                info += "\nVector3D object 2 components: " + ToString(testObject2);
                info += "Expected values: " + ToString(input.result);
                info += "\nActual values: " + ToString(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult.GetX(), input.result[0]));
                REQUIRE(ApproximatelyEqual(testResult.GetY(), input.result[1]));
                REQUIRE(ApproximatelyEqual(testResult.GetZ(), input.result[2]));
            }
        }
    }
}

SCENARIO("A Vector3D can be subtracted from another Vector3D and the resulting object contains mathematically correct values", "[Vector3D]")
{
    std::vector<TestOperatorData> testData =
    {
        {{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}},
        {{0.0, 0.0, 0.0}, {1.0, 2.0, 3.0}, {-1.0, -2.0, -3.0}},
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -2.0, -3.0}, {1.0, 2.0, 3.0}, {-2.0, -4.0, -6.0}},
        {{-2.0, -4.0, -8.0}, {-1.0, -1.0, -1.0}, {-1.0, -3.0, -7.0}},
        {{-2.5, -4.5, -8.5}, {-1.4, -1.4, -1.4}, {-1.1, -3.1, -7.1}}
    };

    WHEN("A Vector3D object is subtracted from another using operator-")
    {
        THEN("All components of the resulting object should be as expected when get functions are called")
        {
            for (auto& input : testData)
            {
                Vector3D testObject1(input.vec1[0], input.vec1[1], input.vec1[2]);
                Vector3D testObject2(input.vec2[0], input.vec2[1], input.vec2[2]);
                Vector3D testResult = testObject1 - testObject2;

                std::string info = "Vector3D object 1 components: " + ToString(testObject1);
                info += "\nVector3D object 2 components: " + ToString(testObject2);
                info += "Expected values: " + ToString(input.result);
                info += "\nActual values: " + ToString(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult.GetX(), input.result[0]));
                REQUIRE(ApproximatelyEqual(testResult.GetY(), input.result[1]));
                REQUIRE(ApproximatelyEqual(testResult.GetZ(), input.result[2]));
            }
        }
    }
}

SCENARIO("The dot product of two Vector3D objects is calculated and the resulting value is mathematically correct", "[Vector3D]")
{
    struct TestDotOperatorData
    {
        std::array<double, 3> vec1;
        std::array<double, 3> vec2;
        double result;
    };

    std::vector<TestDotOperatorData> testData =
    {
        {{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, 14.0},
        {{0.0, 0.0, 0.0}, {1.0, 2.0, 3.0}, 0.0},
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0.0},
        {{-1.0, -2.0, -3.0}, {1.0, 2.0, 3.0}, -14.0},
        {{-2.0, -4.0, -8.0}, {-1.0, -1.0, -1.0}, 14.0},
        {{-2.2, -4.4, -8.8}, {-1.1, -1.1, -1.1}, 16.94}
    };

    WHEN("A dot product is calculated using operator*")
    {
        THEN("All components of the resulting object should be as expected when get functions are called")
        {
            for (auto& input : testData)
            {
                Vector3D testObject1(input.vec1[0], input.vec1[1], input.vec1[2]);
                Vector3D testObject2(input.vec2[0], input.vec2[1], input.vec2[2]);
                double testResult = testObject1 * testObject2;

                std::string info = "Vector3D object 1 components: " + ToString(testObject1);
                info += "\nVector3D object 2 components: " + ToString(testObject2);
                info += "\nExpected value:  " + std::to_string(input.result);
                info += "\nActual value: " + std::to_string(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult, input.result));
            }
        }
    }
}

SCENARIO("The cross product of two Vector3D objects is calculated and the resulting object contains mathematically correct values", "[Vector3D]")
{
    std::vector<TestOperatorData> testData =
    {
        {{1.0, 2.0, 3.0}, {1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}},
        {{0.0, 0.0, 0.0}, {1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}},
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
        {{-1.0, -2.0, -3.0}, {1.0, 2.0, 3.0}, {0.0, 0.0, 0.0}},
        {{-2.0, -4.0, -8.0}, {-1.0, -1.0, -1.0}, {-4.0, 6.0, -2.0}},
        {{3.0, 2.0, 1.0}, {1.0, 2.0, 3.0}, {4.0, -8.0, 4.0}},
        {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}, {-3.63, 7.26, -3.63}}
    };

    WHEN("A cross product is calculated using operator^")
    {
        THEN("All components of the resulting object should be as expected when get functions are called")
        {
            for (auto& input : testData)
            {
                Vector3D testObject1(input.vec1[0], input.vec1[1], input.vec1[2]);
                Vector3D testObject2(input.vec2[0], input.vec2[1], input.vec2[2]);
                Vector3D testResult = testObject1 ^ testObject2;

                std::string info = "Vector3D object 1 components: " + ToString(testObject1);
                info += "\nVector3D object 2 components: " + ToString(testObject2);
                info += "\nExpected values: " + ToString(input.result);
                info += "\nActual values: " + ToString(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult.GetX(), input.result[0]));
                REQUIRE(ApproximatelyEqual(testResult.GetY(), input.result[1]));
                REQUIRE(ApproximatelyEqual(testResult.GetZ(), input.result[2]));
            }
        }
    }
}

SCENARIO("A Vector3D can be multiplied with a scalar and the resulting object contains mathematically correct values", "[Vector3D]")
{
    struct TestScalarOperatorData
    {
        std::array<double, 3> vec;
        double scalar;
        std::array<double, 3> result;
    };

    std::vector<TestScalarOperatorData> testData =
    {
        {{1.0, 2.0, 3.0}, 3.0, {3.0, 6.0, 9.0}},
        {{1.0, 2.0, 3.0}, 1.0, {1.0, 2.0, 3.0}},
        {{0.0, 0.0, 0.0}, 10.0, {0.0, 0.0, 0.0}},
        {{1.0, 2.0, 3.0}, 0.0, {0.0, 0.0, 0.0}},
        {{-1.0, -2.0, -3.0}, 5.0, {-5.0, -10.0, -15.0}},
        {{-2.0, -4.0, -8.0}, -2.0, {4.0, 8.0, 16.0}}
    };

    WHEN("A Vector3D object is multiplied with a scalar using operator*")
    {
        THEN("All components of the resulting object should be as expected when get functions are called")
        {
            for (auto& input : testData)
            {
                Vector3D testObject(input.vec[0], input.vec[1], input.vec[2]);
                Vector3D testResult = testObject * input.scalar;

                std::string info = "Vector3D object components: " + ToString(testObject);
                info += "\nScalar value: " + std::to_string(input.scalar);
                info += "\nExpected values: " + ToString(input.result);
                info += "\nActual values: " + ToString(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult.GetX(), input.result[0]));
                REQUIRE(ApproximatelyEqual(testResult.GetY(), input.result[1]));
                REQUIRE(ApproximatelyEqual(testResult.GetZ(), input.result[2]));
            }
        }
    }
}

SCENARIO("A Vector3D can correctly calculate and return its own length using the length function", "[Vector3D]")
{
    // Vector, expected length
    std::vector<std::pair<std::array<double, 3>, double>> testData =
    {
        {{1.0, 0.0, 0.0}, 1.0},
        {{0.0, 1.0, 0.0}, 1.0},
        {{0.0, 0.0, 1.0}, 1.0},
        {{-1.0, 0.0, 0.0}, 1.0},
        {{0.0, -1.0, 0.0}, 1.0},
        {{0.0, 0.0, -1.0}, 1.0},
        {{10.0, 0.0, 0.0}, 10.0},
        {{0.0, 13.37, 0.0}, 13.37},
        {{0.0, 0.0, -4.2}, 4.2},
        {{1.0, 1.0, 0.0}, 1.4142135},
        {{0.0, 1.0, 1.0}, 1.4142135},
        {{1.0, 0.0, 1.0}, 1.4142135},
        {{1.0, 1.0, 1.0}, 1.7320508},
        {{-1.0, -1.0, -1.0}, 1.7320508},
        {{2.0, 2.0, 0.0}, 2.8284271},
        {{0.0, 2.0, 2.0}, 2.8284271},
        {{2.0, 0.0, 2.0}, 2.8284271},
        {{-2.0, 2.0, 0.0}, 2.8284271},
        {{2.0, -2.0, 0.0}, 2.8284271},
        {{2.0, 1.0, 0.0}, 2.2360679},
        {{-2.0, 1.0, 0.0}, 2.2360679},
        {{2.0, -1.0, 0.0}, 2.2360679},
        {{1.5, 1.5, 0.0}, 2.1213203},
        {{-1.5, 1.5, 0.0}, 2.1213203},
        {{1.5, -1.5, 0.0}, 2.1213203},
        {{-1.5, -1.5, 0.0}, 2.1213203},
        {{0.0, 1.5, 10.0}, 10.1118742},
        {{0.0, -1.5, 10.0}, 10.1118742},
        {{0.0, 1.5, -10.0}, 10.1118742},
        {{0.0, -0.5, -0.866025}, 1.0},
        {{0.316227, -0.948681, 0.0}, 1.0},
    };

    WHEN("The length of a Vector3D object is calculated using the length function")
    {
        THEN("A mathematically correct length value is returned")
        {
            for (auto& input : testData)
            {
                auto& vecData = input.first;
                Vector3D testObject(vecData[0], vecData[1], vecData[2]);
                double testResult = testObject.Length();

                std::string info = "Vector3D object components: " + ToString(testObject);
                info += "\nExpected value: " + std::to_string(input.second);
                info += "\nActual value: " + std::to_string(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult, input.second));
            }
        }
    }
}

SCENARIO("A Vector3D can correctly normalize itself using the normalize function", "[Vector3D]")
{
    // Vector, normalized version
    std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>> testData =
    {
        {{1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}},
        {{0.0, 1.0, 0.0}, {0.0, 1.0, 0.0}},
        {{0.0, 0.0, 1.0}, {0.0, 0.0, 1.0}},
        {{-1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}},
        {{0.0, -1.0, 0.0}, {0.0, -1.0, 0.0}},
        {{0.0, 0.0, -1.0}, {0.0, 0.0, -1.0}},
        {{2.0, 0.0, 0.0}, {1.0, 0.0, 0.0}},
        {{0.0, 33.33, 0.0}, {0.0, 1.0, 0.0}},
        {{0.0, 0.0, -12.34}, {0.0, 0.0, -1.0}},
        {{1.0, 1.0, 0.0}, {0.707106, 0.707106, 0.0}},
        {{0.0, 1.0, 1.0}, {0.0, 0.707106, 0.707106}},
        {{1.0, 0.0, 1.0}, {0.707106, 0.0, 0.707106}},
        {{-1.0, 1.0, 0.0}, {-0.707106, 0.707106, 0.0}},
        {{0.0, -1.0, -1.0}, {0.0, -0.707106, -0.707106}},
        {{0.0, 2.0, 2.0}, {0.0, 0.707106, 0.707106}},
        {{123.456, 0.0, 123.456}, {0.707106, 0.0, 0.707106}},
        {{-144.120, 144.120, 0.0}, {-0.707106, 0.707106, 0.0}},
        {{0.0, -987.654, -987.654}, {0.0, -0.707106, -0.707106}},
        {{3.0, 0.0, 1.0}, {0.948681, 0.0, 0.316227}},
        {{1.0, -3.0, 0.0}, {0.316227, -0.948681, 0.0}},
        {{0.0, -1.0, -3.0}, {0.0, -0.316227, -0.948681}},
    };

    WHEN("A Vector3D object is normalized using the normalize function")
    {
        THEN("The object is correctly normalized after the operation")
        {
            for (auto& input : testData)
            {
                auto& vecData = input.first;
                Vector3D testObject(vecData[0], vecData[1], vecData[2]);
                Vector3D beforeNormalized = testObject;
                testObject.Normalize();
                Vector3D testResult = testObject;

                std::string info = "Vector3D object components before normalization: " + ToString(beforeNormalized);
                info += "\nExpected values: " + ToString(input.second);
                info += "\nActual values: " + ToString(testResult);

                INFO(info);
                REQUIRE(ApproximatelyEqual(testResult.GetX(), input.second[0]));
                REQUIRE(ApproximatelyEqual(testResult.GetY(), input.second[1]));
                REQUIRE(ApproximatelyEqual(testResult.GetZ(), input.second[2]));
            }
        }
    }
}