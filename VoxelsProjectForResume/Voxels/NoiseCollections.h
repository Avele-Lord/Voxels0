#pragma once
// Refactored 19.04.2021	// Looked Through 15.09.2021
#include "FastNoiseLite.h" // need


struct NoiseCollection
{
	FastNoiseLite::NoiseType NoiseType;
	FastNoiseLite::FractalType FractalType;
	FastNoiseLite::CellularDistanceFunction CellularDistanceFunction;
	FastNoiseLite::CellularReturnType CellularReturnType;
	FastNoiseLite::DomainWarpType DomainWarpType;
	FastNoiseLite::RotationType3D RotationType3D;
	int Seed;
	float Frequency;
	int FractalOctaves;
	float FractalLacunarity;
	float FractalWeightedStrength;
	float FractalPingPongStrength;
	float FractalGain;
	float CellularJitter;
	float DomainWarpAmp;
	float XMult;
	float YMult; 
    ///	float ZMult = 1.0f;   Add later
	float Weight;
	///float Freq = 1.0f;  Add later
	bool ClampIsOn;
	float MinClamp;
	float MaxClamp;
};





/////////////////////////////////////////////////////////////////////////////
//////////////////////////      NOISECOLLECTIONS       //////////////////////
/////////////////////////////////////////////////////////////////////////////
struct NoiseDefault : NoiseCollection
{
	NoiseDefault()
	{
		NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin;
		FractalType = FastNoiseLite::FractalType::FractalType_PingPong;
		CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan;
		CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue;
		DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid;
		RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes;
		Seed = 19937;
		Frequency = 0.021f;
		FractalOctaves = 7;
		FractalLacunarity = 2.5f;
		FractalWeightedStrength = 2.70f;
		FractalPingPongStrength = 3.9f;
		FractalGain = 0.7f;
		CellularJitter = 25.5f;
		DomainWarpAmp = 0.018f;
		XMult = 1.0f;
		YMult = 1.0f;
		Weight = 1.0f;
		ClampIsOn = false;
		MinClamp = -10.f;
		MaxClamp = 30.f;
	}
};


/*
struct Noise0 : NoiseCollection
{
	Noise0()
	{
		NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin;
		FractalType = FastNoiseLite::FractalType::FractalType_PingPong;
		CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan;
		CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue;
		DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid;
		RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes;
		Seed = 19937;
		Frequency = 0.0021F;
		FractalOctaves = 7;
		FractalLacunarity = 2.5f;
		FractalWeightedStrength = 2.70f;
		FractalPingPongStrength = 3.9f;
		FractalGain = 0.7f;
		CellularJitter = 25.5f;
		DomainWarpAmp = 0.018f;
		XMult = 1.0f;
		YMult = 1.0f;
		Weight = 1.0f;
		ClampIsOn = false;
		MinClamp = -10.f;
		MaxClamp = 30.f;
	}
};
*/

/*
struct Noise1 : NoiseCollection
{
	Noise1()
	{
		NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin;
		FractalType = FastNoiseLite::FractalType::FractalType_PingPong;
		CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan;
		CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue;
		DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid;
		RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes;
		Seed = 19937;
		Frequency = 0.021f;
		FractalOctaves = 7;
		FractalLacunarity = 2.5f;
		FractalWeightedStrength = 2.70f;
		FractalPingPongStrength = 3.9f;
		FractalGain = 0.7f;
		CellularJitter = 25.5f;
		DomainWarpAmp = 0.018f;
		XMult = 1.0f;
		YMult = 1.0f;
		Weight = 1.0f;
		ClampIsOn = false;
		MinClamp = -10.f;
		MaxClamp = 30.f;
	}
};
*/

/*
struct Noise2 : NoiseCollection
{
	Noise2()
	{
		NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin;
		FractalType = FastNoiseLite::FractalType::FractalType_PingPong;
		CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan;
		CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue;
		DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid;
		RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes;
		Seed = 19937;
		Frequency = 0.0021F;
		FractalOctaves = 7;
		FractalLacunarity = 2.5f;
		FractalWeightedStrength = 2.70f;
		FractalPingPongStrength = 3.9f;
		FractalGain = 0.7f;
		CellularJitter = 25.5f;
		DomainWarpAmp = 0.018f;
		XMult = 1.011f;
		YMult = 1.011f;
		Weight = 520.0f;
		ClampIsOn = false;
		MinClamp = -10.f;
		MaxClamp = 30.f;
		//ZVoxelCords 1.0f;
	}
};
*/