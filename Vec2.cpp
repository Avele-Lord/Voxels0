// Refactored 01.05.2021	// Looked Through 15.09.2021
#include "Vec2.h" // need
#include <cmath> // need


Vec2::Vec2(float X, float Y)
	:
	X(X),
	Y(Y)
{};
bool Vec2::operator == (Vec2 Vec2)
{
	if (X == Vec2.X && Y == Vec2.Y)
	{
		return true;
	}
	return false;
}

Vec2 Vec2::operator+(const Vec2& rhs) const
{
	return Vec2(X + rhs.X, Y + rhs.Y);
}

Vec2& Vec2::operator+=(const Vec2& rhs)
{
	return *this = *this + rhs;
}

Vec2 Vec2::operator*(float rhs) const
{
	return Vec2(X * rhs, Y * rhs);
}

Vec2& Vec2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(X - rhs.X, Y - rhs.Y);
}

Vec2& Vec2::operator-=(const Vec2& rhs)
{
	return *this = *this - rhs;
}

float Vec2::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

float Vec2::GetLengthSq() const
{
	return X * X + Y * Y;
}

Vec2& Vec2::Normalize()
{
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const
{
	const float len = GetLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}