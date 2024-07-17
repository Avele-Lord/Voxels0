#pragma once
// Refactored 28.10.2021	// Looked Through 15.09.2021
#include "Chunk.h" // need
#include "Vec3.h" // need
#include "Noise.h" // need


enum class AdjacentChunkGeneratorState
{
	RightAdjacentChunkGeneratorStateIsBound, 
	LeftAdjacentChunkGeneratorStateIsBound, 
	TopAdjacentChunkGeneratorStateIsBound,
	BottomAdjacentChunkGeneratorStateIsBound,
	FrontAdjacentChunkGeneratorStateIsBound, 
	BackAdjacentChunkGeneratorStateIsBound, 
	AdjacentChunkGeneratorIsNotBound 
};

struct ChunkMesh
{
	std::unique_ptr<class Chunk> AChunk; // A stands for a chunk ( one chunk ) 
	std::vector<class BDS::Vertex> Vertices;
	std::vector<unsigned short> Indices;
	std::vector<class BDS::Color> Colors;
	std::vector<class BDS::ColorGradient> ColorGradients;
};



class ChunkGenerator
{
public:
	ChunkGenerator(const Vec3 ChunksPos, const int ChunkX, const int ChunkY, const int ChunkZ, class Graphics& Gfx);
	void GenerateChunk();
	bool SetVoxel(int VoxelIndexCords, int VoxelToSetTo, int DamageDealtToBlock, int PrevVoxelIndexCords, ChunkGenerator* PrevChunk);
	void BindAdjacentChunkGenerator(ChunkGenerator* AdjacentChunkGenerator, AdjacentChunkGeneratorState AdjacentChunkGeneratorState);
	bool AllAdjacentChunkGeneratorsAreNotEmpty();
	bool AdjacentChunkGeneratorsIsBound(AdjacentChunkGeneratorState AdjacentChunkGeneratorState);
	bool AllAdjacentChunkGeneratorsAreBound();
	bool CheckCollisionDetection(int Value);
	void ClearChunkMesh();
	bool ChunkHasBeenGenerated();
	std::vector<short> GetChunkFields() const;
	std::vector<short>& GetChunkFieldsNotConstReference();
	std::pair<std::vector<Vec3>, std::vector<int>> GetVoxelPos() const;
	ChunkMesh* GetChunkMesh();
	std::vector<ChunkGenerator*>& GetAdjacentChunkGenerators();
private:
	std::vector<FastNoiseLite> Noise3DInit();
	std::vector<int> CalculateChunkNoise();
	bool InRange(int Value, int Range);


private:
	class Graphics& Gfx; // Do I Need it here ???
	ChunkMesh AChunkMesh;
	std::pair<std::vector<Vec3>, std::vector<int>> VoxelCoordinates;
	std::vector<short> ChunkFields;
	std::vector<unsigned char> ColorGradients;
	std::vector<unsigned char> VoxelsHP; // i'll need to implement SOMHOW filling this array in one fell swoop(at least once seporet function on generation and seporet function when i destry blocks IN ANY WAY (boms or piaks doesnt matter) COS AS OF RIGTH NOW i'm fillign this array in liek 10 places and it's ain pridy I JUST NEED SPE FUNCITON which runs on loop and going through all the evlements of blocks and usigning HP to echk block!!!
	std::vector<NoiseCalculator::NoiseParameters> NoiseParams; // I DON'T NEED IT IN CLASS it should be temp variable I JUST WASTE MY RAM! 
	int NumberOfVirtualChunkEdges; // do not move it on the bottom COS LOOK AT INIT LIST               
	// Row pointer DON'T FORGET TO MANAGE DATA DELET AND SET TO NULLPTR OR BAD TIMES!
	std::vector<ChunkGenerator*> AdjacentChunkGenerators;// The order ChunkGenerator the same as in ChunkEdges RightAdjacentChunkGenerator LeftAdjacentChunkGenerator FrontAdjacentChunkGenerator  BackAdjacentChunkGenerator // 4 of AdjacentChunkGenerators 
	std::vector<AdjacentChunkGeneratorState> AdjacentChunkGeneratorsStates;
	const Vec3 ChunksPos;
	const int ChunkXIndex;
	const int ChunkYIndex;
	const int ChunkZIndex;
	// Make static variables to don't waste memory cos some of these variables are the same for every chunk
	const float VoxelSizeHalf;
	const int VoxelPosX;
	const int VoxelPosY;
	const int VoxelPosZ;
	const int ColorGradient;
	bool ChunkHasBeenGeneratedBool;
	/// DON'T YOU EVER DELETE THIS This makes some cool floors each 20 blocks
	//int Random = 0;
};