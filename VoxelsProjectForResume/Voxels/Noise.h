#pragma once
// Refactored 19.04.2021	// Looked Through 15.09.2021
#include "NoiseCollections.h" // need 
#include <vector> // need 


class NoiseCalculator
{
public:
	class NoiseParameters
	{
	public:
		NoiseParameters()
		{};
		NoiseParameters(
			FastNoiseLite::NoiseType NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin,
			FastNoiseLite::FractalType FractalType = FastNoiseLite::FractalType::FractalType_PingPong,
			FastNoiseLite::CellularDistanceFunction CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan,
			FastNoiseLite::CellularReturnType CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue,
			FastNoiseLite::DomainWarpType DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid,
			FastNoiseLite::RotationType3D RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes,
			int Seed = 19937, float Frequency = 0.021f, int FractalOctaves = 7, float FractalLacunarity = 2.5f,
			float FractalWeightedStrength = 2.70f, float FractalPingPongStrength = 3.9f, float FractalGain = 0.7f,
			float CellularJitter = 25.5f, float DomainWarpAmp = 0.018f,
			float In_XMult = 1.0f, float In_YMult = 1.0f, float In_Weight = 1.0f, bool In_ClampIsOn = false, float In_MinClamp = -10.f, float In_MaxClamp = 30.f);


		NoiseParameters(NoiseCollection& NoiseCollection);


	public:
		float XMult = 1.0f;
		float YMult = 1.0f;
		float Weight = 1.0f;
		bool ClampIsOn = false;
		float MinClamp = -10.f;
		float MaxClamp = 30.f;
		FastNoiseLite Noise;
	};



public:
	NoiseCalculator(int ChunkXIndex, int ChunkYIndex);
	std::vector<int> CalculateNoise(std::vector<NoiseParameters>& NoiseParams);
private:
	float GetNoise(NoiseParameters& Noise, float XVoxelCords, float YVoxelCords);


private:
	int ChunkXIndex;
	int ChunkYIndex;
};