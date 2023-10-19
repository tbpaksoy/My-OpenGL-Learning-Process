#include "Surface.h"

std::vector<float> Surface::GetData()
{
	std::vector<float> result;

	for (Edge* e : edges) for (float f : e->GetData())result.push_back(f);

	return result;
}
std::vector<Vertex*> Surface::GetVertices()
{
	std::vector<Vertex*> result;
	
	for(Edge *edge : edges) 
	{
		result.push_back(edge->a);
		result.push_back(edge->b);
	}

	return result;
}
bool Surface::AbleToDraw()
{
	return edges.size() > 2;
}
Surface::Surface(){}
Surface::Surface(std::vector<Vertex*> vertices)
{
	if(vertices.size() > 2)
		for (int i = 0; i < vertices.size() - 1; i++) 
		{
			vertices.push_back(vertices[i]);
			vertices.push_back(vertices[i + 1]);
		}
}
Surface::Surface(std::vector<Vector3D> pos, std::vector<Vector3D> col)
{
	if (pos.size() > 2 && pos.size() == col.size())
		for (int i = 0; i < pos.size() - 1; i++) 
		{
			edges.push_back(
				new Edge(new Vertex(pos[i + 1], col[i + 1]),new Vertex(pos[i + 1], col[i + 1]))
			);
		}
}
Surface::~Surface(){}