// Refactored 20.05.2021	// Looked Through 15.09.2021
#include "Noise.h" // need 
#include "ConstantsChunkGenerator.h" // need 
#include <algorithm> // need 


NoiseCalculator::NoiseCalculator(int ChunkXIndex,int ChunkYIndex)
	:
	ChunkXIndex(ChunkXIndex),
	ChunkYIndex(ChunkYIndex)
{}


float NoiseCalculator::GetNoise(NoiseParameters& NoiseParams, float XVoxelCords, float YVoxelCords)
{
	if (NoiseParams.ClampIsOn)return std::clamp((NoiseParams.Noise.GetNoise(XVoxelCords * NoiseParams.XMult, YVoxelCords * NoiseParams.YMult/*, 11111100.0f 311111100.0f 501111100.0f 3001111100.0f 1001111100.0f 101111100.0f 1001111100.0f 1.0f Try these realy cool*/) * NoiseParams.Weight), NoiseParams.MinClamp, NoiseParams.MaxClamp);
	else return (NoiseParams.Noise.GetNoise(XVoxelCords * NoiseParams.XMult, YVoxelCords * NoiseParams.YMult/*, 11111100.0f   311111100.0f 501111100.0f 3001111100.-f 1001111100.0f 101111100.0f 1001111100.0f 1.0f Try these realy cool */) * NoiseParams.Weight);
}


std::vector<int> NoiseCalculator::CalculateNoise(std::vector<NoiseParameters>& NoiseParams)
{
	std::vector<int> Noise2DArray;
	int LastIndex = ChunkDimensionsLength;
	for (int y = 0; y < LastIndex; y++)
	{
		float YVoxelCords = (float)(y + (ChunkYIndex * ChunkDimensionsLength));
		for (int x = 0; x < LastIndex; x++)
		{
			float XVoxelCords = (float)(x + (ChunkXIndex * ChunkDimensionsLength));
			float NoisePasses = 0.0f;
			for (int i = 0; i < (int)NoiseParams.size(); i++)
			{
				NoisePasses += GetNoise(NoiseParams[i], XVoxelCords, YVoxelCords);
			}
			Noise2DArray.push_back((int)NoisePasses);
		}
	}
	return Noise2DArray;
}



NoiseCalculator::NoiseParameters::NoiseParameters(FastNoiseLite::NoiseType NoiseType, FastNoiseLite::FractalType FractalType, FastNoiseLite::CellularDistanceFunction CellularDistanceFunction, FastNoiseLite::CellularReturnType CellularReturnType, FastNoiseLite::DomainWarpType DomainWarpType, FastNoiseLite::RotationType3D RotationType3D, int Seed, float Frequency, int FractalOctaves, float FractalLacunarity, float FractalWeightedStrength, float FractalPingPongStrength, float FractalGain, float CellularJitter, float DomainWarpAmp, float In_XMult, float In_YMult, float In_Weight, bool In_ClampIsOn, float In_MinClamp, float In_MaxClamp)
	:
	XMult(XMult),
	YMult(YMult),
	Weight(Weight),
	ClampIsOn(ClampIsOn),
	MinClamp(MinClamp),
	MaxClamp(MaxClamp)
{
	Noise.SetNoiseType(NoiseType);
	Noise.SetFractalType(FractalType);
	Noise.SetCellularDistanceFunction(CellularDistanceFunction);
	Noise.SetCellularReturnType(CellularReturnType);
	Noise.SetDomainWarpType(DomainWarpType);
	Noise.SetRotationType3D(RotationType3D);
	Noise.SetSeed(Seed);
	Noise.SetFrequency(Frequency);
	Noise.SetFractalOctaves(FractalOctaves);
	Noise.SetFractalLacunarity(FractalLacunarity);
	Noise.SetFractalWeightedStrength(FractalWeightedStrength);
	Noise.SetFractalPingPongStrength(FractalPingPongStrength);
	Noise.SetFractalGain(FractalGain);
	Noise.SetCellularJitter(CellularJitter);
	Noise.SetDomainWarpAmp(DomainWarpAmp);
	XMult = In_XMult;
	YMult = In_YMult;
	Weight = In_Weight;
	ClampIsOn = In_ClampIsOn;
	MinClamp = In_MinClamp;
	MaxClamp = In_MaxClamp;
}


NoiseCalculator::NoiseParameters::NoiseParameters(NoiseCollection& NoiseCollection)
	:
	XMult(NoiseCollection.XMult),
	YMult(NoiseCollection.YMult),
	Weight(NoiseCollection.Weight),
	ClampIsOn(NoiseCollection.ClampIsOn),
	MinClamp(NoiseCollection.MinClamp),
	MaxClamp(NoiseCollection.MaxClamp)
{
	Noise.SetNoiseType(NoiseCollection.NoiseType);
	Noise.SetFractalType(NoiseCollection.FractalType);
	Noise.SetCellularDistanceFunction(NoiseCollection.CellularDistanceFunction);
	Noise.SetCellularReturnType(NoiseCollection.CellularReturnType);
	Noise.SetDomainWarpType(NoiseCollection.DomainWarpType);
	Noise.SetRotationType3D(NoiseCollection.RotationType3D);
	Noise.SetSeed(NoiseCollection.Seed);
	Noise.SetFrequency(NoiseCollection.Frequency);
	Noise.SetFractalOctaves(NoiseCollection.FractalOctaves);
	Noise.SetFractalLacunarity(NoiseCollection.FractalLacunarity);
	Noise.SetFractalWeightedStrength(NoiseCollection.FractalWeightedStrength);
	Noise.SetFractalPingPongStrength(NoiseCollection.FractalPingPongStrength);
	Noise.SetFractalGain(NoiseCollection.FractalGain);
	Noise.SetCellularJitter(NoiseCollection.CellularJitter);
	Noise.SetDomainWarpAmp(NoiseCollection.DomainWarpAmp);
	XMult = NoiseCollection.XMult;
	YMult = NoiseCollection.YMult;
	Weight = NoiseCollection.Weight;
	ClampIsOn = NoiseCollection.ClampIsOn;
	MinClamp = NoiseCollection.MinClamp;
	MaxClamp = NoiseCollection.MaxClamp;
}