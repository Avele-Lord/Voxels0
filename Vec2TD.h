#pragma once
// Refactored 20.04.2021	// Looked Through 15.09.2021


class Vec2TD
{
public:
	Vec2TD() = default;
	Vec2TD(float X, float Z);
	bool operator == (Vec2TD Vec2TD);
	Vec2TD operator+(const Vec2TD& rhs) const;
	Vec2TD& operator+=(const Vec2TD& rhs);
	Vec2TD operator*(float rhs) const;
	Vec2TD& operator*=(float rhs);
	Vec2TD operator-(const Vec2TD& rhs) const;
	Vec2TD& operator-=(const Vec2TD& rhs);
	float GetLength() const;
	float GetLengthSq() const;
	Vec2TD& Normalize();
	Vec2TD GetNormalized() const;



public:
	float X;
	float Z;
};