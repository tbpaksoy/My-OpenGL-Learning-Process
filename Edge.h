#include "Vertex.h"
#pragma once

class Edge
{
public:
	Vertex* a = nullptr, * b = nullptr;
	Edge(Vertex *a, Vertex *b);
	std::vector<float> GetData();
};