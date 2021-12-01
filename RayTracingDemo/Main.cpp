#include <cstdint>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Ray.h"
#include "Disc.h"
#include "Sphere.h"
#include "OBB.h"
#include "Triangle.h"
#include "Plane.h"
#include "Scene.h"

int main()
{
	const unsigned int width = 1024;
	const unsigned int height = 1024;
	const int channels = 3;
	// uint8_t = unsigned integer type consisting of 8 bits, often just unsigned char in the background
	uint8_t* imageData = new uint8_t[width * height * channels];

	// This is the main function in which you should create shapes and use them to ray trace a simple scene containing the shapes
	// It is ok to create helper functions and utelize them
	// Make sure that you pass all of the automatic tests before implementing this part

	// To switch which main function is being used, exclude either this file from the build, or all the test files
	// Right click file, properties, configuration properties, general, exclude from build = Yes/No
	Scene scene(
		Vector3D(-3, 2.2, 3), // Camera position
		Vector3D(1, -0.2, -1), // Camera direction
		2.0, // Camera size
		// Shapes
		OBB(Vector3D(0, 1, 1), Vector3D(0, 0, 0), Vector3D(1, 0, 0), Vector3D(0, 1, 0), Vector3D(0, 0, 1), 2, 2, 1),
		Sphere(Vector3D(1, 0, 0), Vector3D(0, 2.5, 0), 1),
		Triangle(Vector3D(0, 1, 0), Vector3D(0, 0, 1), Vector3D(0, 0, 3), Vector3D(0, 3, 2)),
		Plane(Vector3D(0.3, 0.3, 0.3), Vector3D(0, -0.5, 0), Vector3D(0, 1, 0))
	);

	scene.render(imageData, width, height);
	
	stbi_write_png("Traced.png", width, height, channels, imageData, width * channels);
	delete[] imageData;
	int a;
	std::cin >> a;
	return 0;
}