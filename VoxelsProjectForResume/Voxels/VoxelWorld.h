#pragma once
// Refactored 29.10.2021	// Looked Through 15.09.2021
#include "Vec2TD.h" // need
#include "Vec3.h"  // Cubic chunks
#include "ChunkGenerator.h" // need


class RayCast;

class VoxelWorld
{
public:
	VoxelWorld(class Window& Wnd, class Camera& Cam);
	~VoxelWorld() = default;
	void GenerateVoxelWorld();
	void UpdatePosition_RemoveChuncs_AddChunks();
	int SetBlock(int VoxelToSet, int DamageDealtToBlock);
	Vec3 GetRayCollision();
	void CollisionDetection(float EntityPosX, float &EntityPosY, float EntityPosZ);
protected:

private:
	void BindAndGenerateAndRenderAllChunks();
	std::tuple<ChunkGenerator*, std::vector<Vec3>*, std::vector<int>*, Vec3, int> FindVoxels(RayCast& Ray);
	RayCast InitVoxelsFinder();


	
public:

protected:

private:
	class Window& Wnd;
	class Camera& Cam;
	std::vector<std::unique_ptr<ChunkGenerator>> Chunks;
	std::vector<Vec3> ChunksCords;
	std::vector<std::vector<Vec3>> VoxelsPos;
	std::vector<std::vector<int>> VoxelsIndex;
	static constexpr AdjacentChunkGeneratorState AdjacentChunkGeneratorsStatesOrderOfEnums[] = { AdjacentChunkGeneratorState::RightAdjacentChunkGeneratorStateIsBound, AdjacentChunkGeneratorState::LeftAdjacentChunkGeneratorStateIsBound, AdjacentChunkGeneratorState::TopAdjacentChunkGeneratorStateIsBound, AdjacentChunkGeneratorState::BottomAdjacentChunkGeneratorStateIsBound, AdjacentChunkGeneratorState::FrontAdjacentChunkGeneratorStateIsBound, AdjacentChunkGeneratorState::BackAdjacentChunkGeneratorStateIsBound }; 
	Vec3 CharacterPosition;
	int RenderRange =  /*2*/ /*1*/  5        + 1; // you need this + 1 COS it's one less than needed cos i cut chunk edges // DO IT PRITIER LATER THO (redo it basicly)
	int ChunkSize;
	int ChunkX = 0;
	int ChunkY = 0;  
	int ChunkZ = 0;
};