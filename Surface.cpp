#include "Surface.h"
std::vector<float> Surface::GetData()
{
	std::vector<float> result;
	for(Vertex* v : GetPoints())
	{
		result.push_back(v->Position().X());
		result.push_back(v->Position().Y());
		result.push_back(v->Position().Z());
		result.push_back(v->Color().X());
		result.push_back(v->Color().Y());
		result.push_back(v->Color().Z());
	}
	return result;
}