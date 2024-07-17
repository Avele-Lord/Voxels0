#pragma once
#ifndef ConstantsChunkGenerator
// Refactored 15.09.2021	// Looked Through 15.09.2021


#define ConstantsChunkGenerator
inline constexpr int VoxelSize{ 1 };
inline constexpr int ChunkDimensionsLength{ 32 };// ChunkLineElements // DO NOT MAKE VALUE TOO BIG USING unsigned short for INDICES in Chunk renderer and IF TOO MANY INDICES CRASH (well not crash it will wrap around AND render incorectly! cos not enogh valye in unsigned short)    
inline constexpr int ChunkSliceElements{ ChunkDimensionsLength * ChunkDimensionsLength };
//inline constexpr int ChunkZElements{ /*ORIGINAL 200*/32 };// rename this to ChunkHeightElements OR somhting like that// DO NOT MAKE VALUE TOO BIG USING unsigned short for INDICES in Chunk renderer and IF TOO MANY INDICES CRASH  (well not crash it will wrap around AND render incorectly!)
inline constexpr int ChunkTotalElements{ ChunkDimensionsLength * ChunkDimensionsLength * ChunkDimensionsLength };// original  NOT Cubic chunks ///////  // inline constexpr int ChunkTotalElements{ ChunkDimensionsLength * ChunkDimensionsLength * ChunkDimensionsLength };       // Cubic chunks

namespace CCG
{

}
#endif