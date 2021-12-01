#include "Scene.h"
#include <algorithm>

Scene::Scene(Vector3D cameraOrigin, Vector3D cameraDirection, double cameraSize) 
	: cameraOrigin(cameraOrigin), cameraDirection(cameraDirection), cameraSize(cameraSize) 
{
	this->cameraDirection.Normalize();
}

Vector3D Scene::trace(Ray ray) {
	//std::cout << "Tracing: <" << ray.origin.GetX() << ", " << ray.origin.GetY() << ", " << ray.origin.GetZ() << ">, <" 
	//	<< ray.direction.GetX() << ", " << ray.direction.GetY() << ", " << ray.direction.GetZ() << ">" << std::endl;
	Vector3D color(0.0, 0.0, 0.0); // Background color
	double min_t = std::numeric_limits<double>::infinity();
	for (Shape* shape : shapes) {
		double t;
		if (shape->Intersection(ray, t)) {
			if (t < min_t) {
				color = shape->GetColour();
				min_t = t;
			}
		}
	}
	//std::cout << min_t << std::endl;
	double light = 1 - min_t / 8;
	if (light < 0) light = 0;
	else if (light > 1) light = 1;
	return color * light;
}

void Scene::render(uint8_t* target, uint32_t width, uint32_t height, uint32_t channels)
{
	// Cross camera direction with up
	Vector3D horizontal = cameraDirection ^ Vector3D(0, 1, 0);
	if (horizontal.Length() < EPS) 
	{
		horizontal = Vector3D(1, 0, 0);
	}
	horizontal.Normalize();
	Vector3D vertical = cameraDirection ^ horizontal;

	Vector3D focalPoint = cameraOrigin - cameraDirection * 2;

	horizontal = horizontal * (cameraSize * (double)width / (double)std::max(width, height));
	vertical = vertical * (cameraSize * (double)height / (double)std::max(width, height));

	for (uint32_t y = 0; y < height; y++)
	{
		Vector3D py = vertical * (((double)y / (double)height) * 2 - 1);
		for (uint32_t x = 0; x < width; x++)
		{
			Vector3D px = horizontal * (((double)x / (double)width) * 2 - 1);

			Vector3D origin = cameraOrigin + py + px;
			Vector3D direction = origin - focalPoint;
			direction.Normalize();

			Vector3D color = trace(Ray(origin, direction));

			// Set color on image
			target[y * width * channels + x * channels + 0] = (uint8_t)(color.GetX() * 255);
			target[y * width * channels + x * channels + 1] = (uint8_t)(color.GetY() * 255);
			target[y * width * channels + x * channels + 2] = (uint8_t)(color.GetZ() * 255);
		}
	}
}

Scene::~Scene()
{
	for (Shape* shape : shapes)
	{
		delete shape;
	}
}