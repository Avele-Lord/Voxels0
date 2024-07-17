#pragma once
// Refactored 13.04.2021	// Looked Through 15.09.2021


class Vec3
{
public:
	Vec3() = default;
	Vec3(float X, float Y, float Z);
	template<typename Vec>
	Vec3(Vec VecDUDE2023); // 2023CH  so what i changed is I RENAME parameter from name "Vec" orginaly that was it as parameter name to well you see it "VecDUDE2023" so change it back to "Vec"
	bool operator == (Vec3 Vec3) const;
	Vec3 operator+(const Vec3& rhs) const;
	Vec3& operator+=(const Vec3& rhs);
	Vec3 operator*(float rhs) const;
	Vec3& operator*=(float rhs);
	Vec3 operator-(const Vec3& rhs) const;
	Vec3& operator-=(const Vec3& rhs);
	float GetLength() const;
	float GetLengthSq() const;
	Vec3& Normalize();
	Vec3 GetNormalized() const;


public:
	float X;
	float Y;
	float Z;
};