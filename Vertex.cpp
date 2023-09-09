#pragma once
#include "Vertex.h"
Vector3D Vertex::Position()
{
	return position;
}
Vector3D Vertex::Color()
{
	return color;
}
std::vector<float> Vertex::GetData()
{
	std::vector<float> result;
	result.push_back(position.X());
	result.push_back(position.Y());
	result.push_back(position.Z());
	result.push_back(color.X());
	result.push_back(color.Y());
	result.push_back(color.Z());
	return result;
}
Vertex::Vertex(){}
Vertex::Vertex(Vector3D position, Vector3D color)
{
	this->position = position;
	this->color = color;
}
Vertex::~Vertex(){}