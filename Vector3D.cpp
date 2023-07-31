#include "Vector3D.h"
Vector3D::Vector3D() 
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
Vector3D::Vector3D(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
Vector3D::~Vector3D(){}
float Vector3D::X()
{
	return x;
}
float Vector3D::Y()
{
	return y;
}
float Vector3D::Z()
{
	return z;
}
