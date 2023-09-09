#pragma once
struct Vector3D
{
private:
	float x, y, z;
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	~Vector3D();
	float X();
	float Y();
	float Z();
	Vector3D operator*(float f);
	Vector3D operator/(float f);
};