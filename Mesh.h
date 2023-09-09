#include <vector>
#include "Vertex.h"
#pragma once
class Mesh
{
private:
	std::vector<Vertex*> vertices;
	std::vector<unsigned int> indices;
public:
	void AssignVertices(std::vector<Vertex*> vertices);
	void AssignIndices(std::vector<unsigned int> indices);
	void AddVertex(Vertex* vertex, bool addIndex = false);
	int Count();
	std::vector<float> GetPositionPoints();
	std::vector<float> GetColorPoints();
	std::vector<float> GetData();
	std::vector<unsigned int> GetIndices();
	Mesh();
	Mesh(std::vector<Vertex*> vertices,  std::vector<unsigned int> indices);
	~Mesh();
};