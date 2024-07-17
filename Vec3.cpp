// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "Vec3.h" // need
#include <cmath> // need


Vec3::Vec3(float X, float Y, float Z)
	:
	X(X),
	Y(Y),
	Z(Z)
{};


template<typename Vec>
Vec3::Vec3(Vec VecDUDE2023) // 2023CH  so what i changed is I RENAME parameter from name "Vec" orginaly that was it as parameter name to well you see it "VecDUDE2023" so change it back to "Vec"
	:
	X(Vec.x),
	Y(Vec.y),
	Z(Vec.z)
{};


bool Vec3::operator == (Vec3 Vec3) const
{
	if (X == Vec3.X && Y == Vec3.Y && Z == Vec3.Z)
	{
		return true;
	}
	return false;
}


Vec3 Vec3::operator+(const Vec3& rhs) const
{
	return Vec3(X + rhs.X, Y + rhs.Y, Z + rhs.Z);
}

Vec3& Vec3::operator+=(const Vec3& rhs)
{
	return *this = *this + rhs;
}

Vec3 Vec3::operator*(float rhs) const
{
	return Vec3(X * rhs, Y * rhs, Z * rhs);
}

Vec3& Vec3::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
	return Vec3(X - rhs.X, Y - rhs.Y, Z - rhs.Z);
}

Vec3& Vec3::operator-=(const Vec3& rhs)
{
	return *this = *this - rhs;
}

float Vec3::GetLength() const
{
	return std::sqrt(GetLengthSq());
}

float Vec3::GetLengthSq() const
{
	return X * X + Y * Y + Z * Z;
}

Vec3& Vec3::Normalize()
{
	return *this = GetNormalized();
}

Vec3 Vec3::GetNormalized() const
{
	const float len = GetLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}