#pragma once
// Refactored ??.??.2021	// Looked Through 15.09.2021
#include <DirectXMath.h> // need


namespace BDS
{
	struct Vertex
	{
		DirectX::XMFLOAT3 Pos;
	};
	struct Color
	{
		short Color;
	};
	struct ColorGradient
	{
		unsigned char ColorGradient;
	};
	struct RandomColor
	{
		DirectX::XMFLOAT3 RandomColor;
	};
	struct Lighting
	{
		DirectX::XMFLOAT3 Color;
		float SpecularIntensity = 0.6f;
		float SpecularPower = 30.0f;
		float Padding[3];
	};
	struct ConstauntBufferVoxelsColors
	{
		struct
		{
			float R;
			float G;
			float B;
			float A;
		} Colors[12];
	};
	struct Transforms
	{
		DirectX::XMMATRIX ModelViewProj;
		DirectX::XMMATRIX Model;
	};
	///Mob Start
	struct ConstauntBufferVoxelsColor
	{
		struct
		{
			float R;
			float G;
			float B;
			float A;
		} Colors;
	};
	struct Instance
	{
		DirectX::XMFLOAT3 Position;
	};
	///Mob end
}