#include "Edge.h"

std::vector<float> Edge::GetData()
{
	std::vector<float> result;

	for (float f : a->GetData()) result.push_back(f);
	for (float f : b->GetData()) result.push_back(f);

	return result;
}
Edge::Edge(Vertex *a, Vertex *b)
{
	this->a = a;
	this->b = b;
}