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
Vertex::Vertex(){}
Vertex::Vertex(Vector3D position, Vector3D color)
{
	this->position = position;
	this->color = color;
}
Vertex::~Vertex(){}