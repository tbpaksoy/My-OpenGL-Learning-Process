#include "Mesh.h"
#include <stdexcept>
void Mesh::AssignVertices(std::vector<Vertex*> vertices)
{
	this->vertices = vertices;
}
void Mesh::AssignIndices(std::vector<unsigned int> indices)
{
	this->indices = indices;
}
int Mesh::Count()
{
	return vertices.size();
}
std::vector<float> Mesh::GetPositionPoints()
{
	if (*std::max(indices.begin(), indices.end()) < vertices.size()) throw std::exception("Maximum index can not be bigger than vertices size.");
	std::vector<float> result;
	for (unsigned int i : indices)
	{
		Vector3D v = vertices[i]->Position();
		result.push_back(v.X());
		result.push_back(v.Y());
		result.push_back(v.Z());
	}
	return result;
}
std::vector<float> Mesh::GetColorPoints()
{
	if (*std::max(indices.begin(), indices.end()) < vertices.size()) throw std::exception("Maximum index can not be bigger than vertices size.");
	std::vector<float> result;
	for (unsigned int i : indices)
	{
		Vector3D v = vertices[i]->Color();
		result.push_back(v.X());
		result.push_back(v.Y());
		result.push_back(v.Z());
	}
	return result;
}
std::vector<float> Mesh::GetData()
{
	std::vector<float> data;
	for(unsigned int i : indices)
	{
		Vertex* vertex = vertices[i];
		Vector3D p = vertices[i]->Position(), c = vertices[i]->Color();
		data.push_back(p.X());
		data.push_back(p.Y());
		data.push_back(p.Z());
		data.push_back(c.X());
		data.push_back(c.Y());
		data.push_back(c.Z());
	}
	return data;
}
std::vector<unsigned int> Mesh::GetIndices()
{
	std::vector<unsigned int> indices;
	for (unsigned int i : this->indices) indices.push_back(i);
	return indices;
}
Mesh::Mesh()
{

}
Mesh::Mesh(std::vector<Vertex*> vertices, std::vector<unsigned int> indices)
{
	this->vertices = vertices;
	this->indices = indices;
}
Mesh::~Mesh(){}