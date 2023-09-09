#include"Surface.h"
#pragma once
class Circle : Surface
{
	float radius;
	unsigned int resolution;
	std::vector<Vertex*> GetPoints() override;
};