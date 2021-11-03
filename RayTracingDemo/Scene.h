#pragma once
#include <vector>
#include <type_traits>

#include "Shape.h"
class Scene
{
	std::vector<Shape*> shapes;
	Vector3D cameraOrigin;
	Vector3D cameraDirection;
	double cameraSize;
public:
	Scene(Vector3D cameraOrigin, Vector3D cameraDirection, double cameraSize) : cameraOrigin(cameraOrigin), cameraDirection(cameraDirection), cameraSize(cameraSize) {
		cameraDirection.Normalize();
	}
	template<class ... Ts>
	Scene(Vector3D cameraOrigin, Vector3D cameraDirection, double cameraSiz, Ts... ts) : Scene(cameraOrigin, cameraDirection, cameraSize)
	{
		addObject(ts...);
	}

	template<class T, class ... Ts>
	void addObject(T shape, Ts... ts) 
	{
		addObject(shape);
		addObject(ts...);
	}

	template<class T>
	void addObject(T shape)
	{
		static_assert(std::is_base_of<Shape, T>::value, "T must inherit from Shape");
		// Copy to heap.
		T* heap_allocated = new T(shape);
		shapes.push_back(heap_allocated);
	}

	void render(uint8_t* target, uint32_t width, uint32_t height) 
	{
		// Cross camera direction with up
		Vector3D horizontal = cameraDirection ^ Vector3D(0, 1, 0);
		Vector3D vertical = cameraDirection ^ horizontal;
		for (uint32_t y = 0; y < height; y++)
		{
			Vector3D y_dir = vertical * (y * cameraSize / height - cameraSize / 2);
			for (uint32_t x = 0; x < width; x++)
			{
				Vector3D x_dir = horizontal * (y * cameraSize / height - cameraSize / 2);
				Vector3D origin = cameraOrigin + vertical + horizontal;
				Ray ray(origin, cameraDirection);
				Vector3D color(0.0, 0.0, 0.0); // Background color
				double min_t = std::numeric_limits<double>::infinity();
				for (Shape* shape : shapes) {
					double t;
					if (shape->Intersection(ray, t)) {
						if (min_t > t) {
							color = shape->GetColour();
							min_t = t;
						}
					}
				}
				// Set color on image
				target[y * width + x + 0] = (uint8_t)(color.GetX() * 255);
				target[y * width + x + 1] = (uint8_t)(color.GetY() * 255);
				target[y * width + x + 2] = (uint8_t)(color.GetZ() * 255);
			}
		}
	}

	~Scene()
	{
		for (Shape* shape : shapes) 
		{
			delete shape;
		}
	}
};



