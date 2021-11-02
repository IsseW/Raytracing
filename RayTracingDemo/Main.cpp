#include <cstdint>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Ray.h"
#include "Disc.h"
#include "Sphere.h"
#include "OBB.h"
#include "Triangle.h"
#include "Plane.h"

int main()
{
	const unsigned int width = 512;
	const unsigned int height = 512;
	const int channels = 3;
	// uint8_t = unsigned integer type consisting of 8 bits, often just unsigned char in the background
	uint8_t* imageData = new uint8_t[width * height * channels];

	// This is the main function in which you should create shapes and use them to ray trace a simple scene containing the shapes
	// It is ok to create helper functions and utelize them
	// Make sure that you pass all of the automatic tests before implementing this part

	// To switch which main function is being used, exclude either this file from the build, or all the test files
	// Right click file, properties, configuration properties, general, exclude from build = Yes/No
	
	stbi_write_png("Traced.png", width, height, channels, imageData, width * channels);
	delete[] imageData;
	return 0;
}