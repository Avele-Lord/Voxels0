#pragma once
// Refactored 14.04.2021	// Looked Through 15.09.2021
//#include <math.h> // Do not delete


constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template <typename T>
constexpr auto Sq(const T& X)
{
	return X * X;
}

template<typename T>
T WrapAngle(T Theta)
{
	const T Modded = fmod(Theta, (T)2.0 * (T)PI_D);
	return (Modded > (T)PI_D) ?
		(Modded - (T)2.0 * (T)PI_D) :
		Modded;
}

template<typename T>
constexpr T Interpolate(const T& Src, const T& Dst, float Alpha)
{
	return Src + (Dst - Src) * Alpha;
}

template<typename T>
constexpr T ToRad(T Deg)
{
	return Deg * PI / (T)180.0;
}