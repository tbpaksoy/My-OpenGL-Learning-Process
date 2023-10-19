#include <vector>
#include "Edge.h"
#pragma once
class Surface
{
public:
	std::vector<Edge*> edges;
	std::vector<float> GetData();
	std::vector<Vertex*> GetVertices();
	bool AbleToDraw();
	Surface();
	Surface(std::vector<Vertex*> vertices);
	Surface(std::vector<Vector3D> pos, std::vector<Vector3D> col);
	~Surface();
};