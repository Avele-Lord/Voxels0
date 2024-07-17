#pragma once
// Refactored 13.04.2021	// Looked Through 15.09.2021
#include "Vec3.h" // need
//#include "Vec2TD.h" // need


class RayCast
{
public:
	RayCast(Vec3 EndLocation, float Pitch, float Yaw);
	std::pair<Vec3, Vec3> ShootARayCast();
	Vec3 GetEndLocation();
private:
	Vec3 EndLocation;
	float Pitch;
	float Yaw;
};