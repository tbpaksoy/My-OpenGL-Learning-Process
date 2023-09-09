#include <vector>
#include "Vertex.h"
#include "Vector3D.h"
#pragma once
class Surface
{
public:
	virtual std::vector<Vertex*> GetPoints() = 0;
	std::vector<float> GetData();
};