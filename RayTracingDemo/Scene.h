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
	Scene(Vector3D cameraOrigin, Vector3D cameraDirection, double cameraSize);
	template<class ... Ts>
	Scene(Vector3D cameraOrigin, Vector3D cameraDirection, double cameraSize, Ts... ts) : Scene(cameraOrigin, cameraDirection, cameraSize)
	{
		addObject(ts...);
	}

	template<class T, class ... Ts>
	void addObject(const T& shape, Ts... ts) 
	{
		addObject(shape);
		addObject(ts...);
	}

	template<class T>
	void addObject(const T& shape)
	{
		static_assert(std::is_base_of<Shape, T>::value, "T must inherit from Shape");
		// Copy to heap.
		T* heap_allocated = new T(shape);
		shapes.push_back(heap_allocated);
	}

	Vector3D trace(Ray ray);

	void render(uint8_t* target, uint32_t width, uint32_t height, uint32_t channels = 3);

	~Scene();
};



