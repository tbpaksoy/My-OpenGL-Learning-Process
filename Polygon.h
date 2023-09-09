#include "Surface.h"
#pragma once
class Polygon : public Surface
{
	std::vector<Vertex*> points;
	std::vector<Vertex*> GetPoints() override;
};