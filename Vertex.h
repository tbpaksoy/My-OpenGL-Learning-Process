#include "Vector3D.h"
#include <vector>
#pragma once
class Vertex
{
private:
	Vector3D position, color;
public:
	Vector3D Position();
	Vector3D Color();
	std::vector<float> GetData();
	Vertex();
	Vertex(Vector3D position, Vector3D color);
	~Vertex();
};