#include "Vector3D.h"
#pragma once
class Vertex
{
private:
	Vector3D position, color;
public:
	Vector3D Position();
	Vector3D Color();
	Vertex();
	Vertex(Vector3D position, Vector3D color);
	~Vertex();
};