// Refactored 01.05.2021	// Looked Through 15.09.2021
#include "Vec2TD.h" // need
#include <cmath> // need


Vec2TD::Vec2TD(float X, float Z)
	:
	X(X),
	Z(Z)
{};
bool Vec2TD::operator == (Vec2TD Vec2TD)
{
	if (X == Vec2TD.X && Z == Vec2TD.Z)
	{
		return true;
	}
	return false;
}

Vec2TD Vec2TD::operator+(const Vec2TD& rhs) const
{
	return Vec2TD(X + rhs.X, Z + rhs.Z);
}

Vec2TD& Vec2TD::operator+=(const Vec2TD& rhs)
{
	return *this = *this + rhs;
}

Vec2TD Vec2TD::operator*(float rhs) const
{
	return Vec2TD(X * rhs, Z * rhs);
}

Vec2TD& Vec2TD::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2TD Vec2TD::operator-(const Vec2TD& rhs) const
{
	return Vec2TD(X - rhs.X, Z - rhs.Z);
}

Vec2TD& Vec2TD::operator-=(const Vec2TD& rhs)
{
	return *this = *this - rhs;
}

float Vec2TD::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

float Vec2TD::GetLengthSq() const
{
	return X * X + Z * Z;
}

Vec2TD& Vec2TD::Normalize()
{
	return *this = GetNormalized();
}

Vec2TD Vec2TD::GetNormalized() const
{
	const float len = GetLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}