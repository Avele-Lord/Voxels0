#pragma once
// Refactored 20.04.2021	// Looked Through 15.09.2021


class Vec2
{
public:
	Vec2() = default;
	Vec2(float X, float Y);
	bool operator == (Vec2 Vec2);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);
	float GetLength() const;
	float GetLengthSq() const;
	Vec2& Normalize();
	Vec2 GetNormalized() const;



public:
	float X;
	float Y;
};