// Refactored 29.10.2021(NON Refactored)	// Looked Through 15.09.2021
#include "Window.h" // need
#include "VoxelWorld.h" // need
#include "RayCast.h" // need
#include "ConstantsChunkGenerator.h" // need
#include "Camera.h" // need


namespace dx = DirectX;


VoxelWorld::VoxelWorld(Window& Wnd, Camera& Cam)
	:
	Wnd(Wnd),
	Cam(Cam),
	ChunkSize(ChunkDimensionsLength * VoxelSize)// This line and the next line can be a bug Watch out!
{}


void VoxelWorld::GenerateVoxelWorld()
{
	for (auto& Chunk : Chunks)
	{
		class Chunk* CurrentChunk = Chunk->GetChunkMesh()->AChunk.get();
		if (!(CurrentChunk == nullptr))
		{
			CurrentChunk->Draw(Wnd.Gfx());
		}
	}
}



// In this function bad variables names refactor
void VoxelWorld::UpdatePosition_RemoveChuncs_AddChunks()
{
	// Updating position of character every tick for spawning and destroying chunks  /// UpdatePosition ///
	dx::XMFLOAT3 XMCamPos = Cam.GetCamPos();
	CharacterPosition = (Vec3(XMCamPos.x, XMCamPos.y, XMCamPos.z));
	int XCharacterPosInChunkCords = int(CharacterPosition.X / (float)ChunkSize);
	int YCharacterPosInChunkCords = int(CharacterPosition.Y / (float)ChunkSize); 
	int ZCharacterPosInChunkCords = int(CharacterPosition.Z / (float)ChunkSize);

	if ((ChunkX != XCharacterPosInChunkCords) || (ChunkZ != ZCharacterPosInChunkCords) || (ChunkY != YCharacterPosInChunkCords))
	{
		ChunkX = XCharacterPosInChunkCords;
		ChunkY = YCharacterPosInChunkCords; 
		ChunkZ = ZCharacterPosInChunkCords;
	}

	// Destroying chunks at runtime   /// RemoveChuncs ///
	for (int i = 0; i < (int)ChunksCords.size(); i++)
	{
		Vec3* ChunksCordsElement = &ChunksCords[i]; 

		float Length = std::sqrtf(std::pow(((((float)ChunkSize * ChunksCordsElement->X) + (float)ChunkSize) - CharacterPosition.X), 2) +
			std::pow(((((float)ChunkSize * ChunksCordsElement->Z) + (float)ChunkSize) - CharacterPosition.Z), 2) +
			std::pow(((((float)ChunkSize * ChunksCordsElement->Y) + (float)ChunkSize) - CharacterPosition.Y), 2));

		if (!(Length < (ChunkSize * (RenderRange + 1))))
			if ((int)Chunks.size() > i)
			{
				// May be preculculate .begin() insted of calling it // on second though if i is 0 then I will delet the iterator to begin and WELL what do you know BAD TIMES that is right
				ChunksCords.erase(ChunksCords.begin() + i);
				Chunks.erase(Chunks.begin() + i);
				VoxelsPos.erase(VoxelsPos.begin() + i);
				VoxelsIndex.erase(VoxelsIndex.begin() + i);
			}
	}


	// Spawning chunks at runtime  ///AddChunk///
	// make RenderRange ++ ( add to it one) cos now my chunks will render on one chunk smaller to bind all adgecient chunks
	for (int x = RenderRange * -1; x <= RenderRange; x++)
	{
		int XChunkIterator = x + ChunkX;
		int XChunkIteratorChunkCords = XChunkIterator * ChunkSize;
		int XChunkIteratorChunkCordsPlusChunkSize = XChunkIteratorChunkCords + ChunkSize;

		// make RenderRange ++ ( add to it one) cos now my chunks will render on one chunk smaller to bind all adgecient chunks
		for (int y = RenderRange * -1; y <= RenderRange; y++)
		{
			int YChunkIterator = y + ChunkY;
			int YChunkIteratorChunkCords = YChunkIterator * ChunkSize;
			int YChunkIteratorChunkCordsPlusChunkSize = YChunkIteratorChunkCords + ChunkSize;
			
			// make RenderRange ++ ( add to it one) cos now my chunks will render on one chunk smaller to bind all adgecient chunks
			for (int z = RenderRange * -1; z < RenderRange; z++)// make RenderRange ++ ( add to it one) cos now my chunks will render on one chunk smaller to bind all adgecient chunks
			{
				int ZChunkIterator = z + ChunkZ;
				int ZChunkIteratorChunkCords = ZChunkIterator * ChunkSize;

				float Length = std::sqrt(std::pow((((/*int // it was int originaly i changed on float i hope I DIND'T BROKE ANYTHING */float)XChunkIteratorChunkCordsPlusChunkSize) - CharacterPosition.X), 2) +
					std::pow(((float)(ZChunkIteratorChunkCords + ChunkSize/* preculculate it the same as i do this 		int XChunkIteratorChunkCordsPlusChunkSize = XChunkIteratorChunkCords + ChunkSize; */) - CharacterPosition.Z), 2) +
					std::pow((((/*int // it was int originaly i changed on float i hope I DIND'T BROKE ANYTHING */float)YChunkIteratorChunkCordsPlusChunkSize) - CharacterPosition.Y), 2));

				if (Length < (ChunkSize * RenderRange))
				{
					Vec3 ChunkIterator((float)XChunkIterator, (float)YChunkIterator, (float)ZChunkIterator); 

					if ((ChunksCords.end() == std::find(ChunksCords.begin(), ChunksCords.end(), ChunkIterator)))
					{
						ChunksCords.push_back(ChunkIterator);
						Chunks.push_back(std::make_unique<ChunkGenerator>(ChunkGenerator(Vec3((float)XChunkIteratorChunkCords,
						(float)YChunkIteratorChunkCords, (float)ZChunkIteratorChunkCords), XChunkIterator, YChunkIterator, ZChunkIterator, Wnd.Gfx())));
						auto[VoxelsCords, Voxelindices] = Chunks[Chunks.size() - 1].get()->GetVoxelPos();
						VoxelsPos.push_back(VoxelsCords);
						VoxelsIndex.push_back(Voxelindices);
					}
				}
			}


		}


	}
	BindAndGenerateAndRenderAllChunks();
}


void VoxelWorld::BindAndGenerateAndRenderAllChunks()
{
	std::vector<Vec3>::iterator ChunksCordsBeginIterator = ChunksCords.begin();
	std::vector<Vec3>::iterator ChunksCordsEndIterator = ChunksCords.end();

	for (int i = 0; i < Chunks.size(); i++)
	{
		// CHECK THIS I RIFECTOR AllAdjacentChunkGeneratorsAreBound() FUNCITON SO THE IS NO CHECK ON CHUNK FIELDS NOT EQUAL TO 0 COS HERE THEY CAN BE EQUL TO ZERO
		//if (!(Chunks[i]->AllAdjacentChunkGeneratorsAreBound()/* && Chunks[i]->AllAdjacentChunkGeneratorsAreNotEmpty() /*uncoment this to get rid of bug*//**/))// Bug Probability 95% // it seems like after i uncoment this i get bad alock on chunk renderer somtims (pass there 0 indecis)
		{
			Vec3 CurrentChunksCords = ChunksCords[i]; 
		    std::vector<Vec3> AdjacentChunksCords = { Vec3(CurrentChunksCords.X + 1.0f, CurrentChunksCords.Y, CurrentChunksCords.Z), Vec3(CurrentChunksCords.X - 1.0f, CurrentChunksCords.Y, CurrentChunksCords.Z), Vec3(CurrentChunksCords.X, CurrentChunksCords.Y + 1.0f, CurrentChunksCords.Z), Vec3(CurrentChunksCords.X, CurrentChunksCords.Y - 1.0f, CurrentChunksCords.Z), Vec3(CurrentChunksCords.X, CurrentChunksCords.Y, CurrentChunksCords.Z + 1.0f) , Vec3(CurrentChunksCords.X, CurrentChunksCords.Y, CurrentChunksCords.Z - 1.0f) };  

			for (int j = 0; j < AdjacentChunksCords.size(); j++)
			{
				//if (!(Chunks[i]->AdjacentChunkGeneratorsIsBound(AdjacentChunkGeneratorsStatesOrderOfEnums[j] /* && Chunks[i]->AllAdjacentChunkGeneratorsAreNotEmpty() /*uncoment this to get rid of bug*//**/)))// Bug Probability 95% // it's correct BUT it's starting alwas crashing game so fix that and it's gonna be a good saving of performance on CPU  // it seems like after i uncoment this i get bad alock on chunk renderer somtims (pass there 0 indecis)
				{
					std::vector<Vec3>::iterator AdjacentChunkCordsIterator = std::find(ChunksCordsBeginIterator, ChunksCordsEndIterator, AdjacentChunksCords[j]); 

					if (!(ChunksCordsEndIterator == AdjacentChunkCordsIterator))
					{
						size_t AdjacentChunkIndex = AdjacentChunkCordsIterator - ChunksCordsBeginIterator; // BTW does it return size_t or int i don't rimember
						Chunks[i]->BindAdjacentChunkGenerator(Chunks[AdjacentChunkIndex].get(), AdjacentChunkGeneratorsStatesOrderOfEnums[j]);
					}
				}
			}
		}

		if (!(Chunks[i]->ChunkHasBeenGenerated()))
		{
			if (Chunks[i]->AllAdjacentChunkGeneratorsAreBound() && Chunks[i]->AllAdjacentChunkGeneratorsAreNotEmpty())
			{
				Chunks[i]->GenerateChunk();
			}
		}
	}

}



// Make SetBlock don't regenerate the whole chunk but only index and vertex buffers( it actualy WIL SAVE A LOT OF PERFORMANCE!!!!)
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// THIS SETBLOCK FUNCITON IS SO SLOW COS  THE MORE CHUNKS THE MORE CHUNKS IT TYRES TO CHECK AND COS OF THAT IT VERY SLOW SO JUST MAKE it so only chunks which can be hit by a ray was check not all chunks in the world(SO i like need sort em and then use find which is realy fast on sirtid containers (like binary search etc)
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int VoxelWorld::SetBlock(int VoxelToSet, int DamageDealtToBlock)
{
	RayCast Ray = InitVoxelsFinder();
	int PrevVoxelCords = 0;
	ChunkGenerator* PrevChunkFound = nullptr;
	int VoxelType = 0;
	int VoxelIndex; 
	bool SetVoxelSuccessful = false;

	for (float Step = 0.0f; Step < 25; Step += 0.1f)
	{
		auto[ChunkFound, VoxelPos, Voxelindices, EndLocation, VoxelCords] = FindVoxels(Ray);

		if (ChunkFound && VoxelCords >= 0 && VoxelCords < ChunkTotalElements)
		{
			std::vector<int>& VoxelindicesTemp = *Voxelindices;
			VoxelIndex = VoxelindicesTemp[VoxelCords];
			VoxelType = ChunkFound->GetChunkFields()[VoxelindicesTemp[VoxelCords]];
		}
		if (ChunkFound ? ChunkFound->SetVoxel(VoxelCords, VoxelToSet, DamageDealtToBlock, PrevVoxelCords, PrevChunkFound) : false)
		{
			if (VoxelIndex <= ChunkTotalElements)
			{
				int VoxelIndexAfterModulusWithChunkSliceElements = VoxelIndex % ChunkSliceElements; 

				if ((ChunkDimensionsLength - 1) == VoxelIndexAfterModulusWithChunkSliceElements % ChunkDimensionsLength)
				{
					ChunkGenerator* RightAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[0];
					RightAdjacentChunkGenerator->ClearChunkMesh();
					RightAdjacentChunkGenerator->GenerateChunk();
				}
				if (0 == VoxelIndexAfterModulusWithChunkSliceElements % ChunkDimensionsLength)
				{
					ChunkGenerator* LeftAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[1];
					LeftAdjacentChunkGenerator->ClearChunkMesh();
					LeftAdjacentChunkGenerator->GenerateChunk();
				}
				///  HERE CAN BE BUGS! on the very last block of a cubic chunk IT WON'T RENDER ENDGESON IT! so watch out! 
				if ((ChunkSliceElements * (ChunkDimensionsLength - 1)) < VoxelIndex)
				{
					ChunkGenerator* TopAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[2];
					TopAdjacentChunkGenerator->ClearChunkMesh(); 
					TopAdjacentChunkGenerator->GenerateChunk();
				}
				if (ChunkSliceElements >= VoxelIndex)
				{
					ChunkGenerator* BottomAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[3];
					BottomAdjacentChunkGenerator->ClearChunkMesh();
					BottomAdjacentChunkGenerator->GenerateChunk();
				}
				if (VoxelIndexAfterModulusWithChunkSliceElements >= ((ChunkDimensionsLength * ChunkDimensionsLength) - ChunkDimensionsLength))
				{
					ChunkGenerator* FrontAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[4];
					FrontAdjacentChunkGenerator->ClearChunkMesh();
					FrontAdjacentChunkGenerator->GenerateChunk();
				}
				if (VoxelIndexAfterModulusWithChunkSliceElements <= ChunkDimensionsLength)
				{
					ChunkGenerator* BackAdjacentChunkGenerator = ChunkFound->GetAdjacentChunkGenerators()[5];
					BackAdjacentChunkGenerator->ClearChunkMesh();
					BackAdjacentChunkGenerator->GenerateChunk();
				}
			}
			break; // if i comment out this break i will be deleting all chunks infront of me by the lenth of ray
		}
		PrevVoxelCords = VoxelCords;
		PrevChunkFound = ChunkFound;
	}
	return VoxelType;
}


std::tuple<ChunkGenerator*, std::vector<Vec3>*, std::vector<int>*, Vec3, int> VoxelWorld::FindVoxels(RayCast& Ray)
{
	auto[EndLocation, EndLocationCorrected] = Ray.ShootARayCast();
	size_t Index = std::find(ChunksCords.begin(), ChunksCords.end(), Vec3(/*Try to use round here too*/float((int)(/*(float)*/std::round(EndLocationCorrected.X) / (float)ChunkDimensionsLength)), float((int)(/*(float)*/std::round(EndLocationCorrected.Y) / (float)ChunkDimensionsLength)), float((int)(/*(float)*/std::round(EndLocationCorrected.Z) / (float)ChunkDimensionsLength)))) - ChunksCords.begin();
	ChunkGenerator* ChunkFound = Index < Chunks.size() ? Chunks[Index].get() : nullptr;
	std::vector<Vec3>* VoxelPos = Index < VoxelsPos.size() ? &VoxelsPos[Index] : nullptr;
	std::vector<int>* Voxelindices = Index < VoxelsIndex.size() ? &VoxelsIndex[Index] : nullptr;
	int VoxelCords = VoxelPos ? std::find(VoxelPos->begin(), VoxelPos->end(), (Vec3(/*ROUND HERE IS CRUCIAL I'VE SPEND A WEEK TO FIGURE OUT WHY THE RAY WAS A BIT SKEWED*/std::round(EndLocation.X), std::round(EndLocation.Y), std::round(EndLocation.Z)))) - VoxelPos->begin() : ChunkTotalElements;
	return { ChunkFound, VoxelPos, Voxelindices, EndLocation, VoxelCords };
}

Vec3 VoxelWorld::GetRayCollision()
{
	RayCast Ray = InitVoxelsFinder();
	for (float Step = 0.0f; Step < 25; Step += 0.1f)
	{
		auto[ChunkFound, VoxelPos, Voxelindices, EndLocation, VoxelCords] = FindVoxels(Ray);
		if (ChunkFound ? ChunkFound->CheckCollisionDetection(VoxelCords) : false) break;
	}
	return Ray.GetEndLocation();
}

RayCast VoxelWorld::InitVoxelsFinder()
{
	dx::XMFLOAT3 CamPos = Cam.GetCamPos();
	Vec3 EndLocation(CamPos.x, CamPos.y, CamPos.z);
	Rotation CamRotation = Cam.GetCamRotation();
	return RayCast(EndLocation, CamRotation.Pitch, CamRotation.Yaw);
}



void VoxelWorld::CollisionDetection(float EntityPosX, float &EntityPosY, float EntityPosZ)
{
	Vec3 EndLocation(EntityPosX, EntityPosY, EntityPosZ);
	Rotation CamRotation = Cam.GetCamRotation();
	RayCast Ray = RayCast(EndLocation, CamRotation.Pitch, CamRotation.Yaw);
	for (float Step = 0.0f; Step < 25; Step += 0.1f)
	{
		auto[ChunkFound, VoxelsPos, Voxelindicess, EndLocation, VoxelCords] = FindVoxels(Ray);
		if (!(ChunkFound == nullptr))
		{
			const std::vector<Vec3>& VoxelPos = *VoxelsPos;
			const std::vector<int>& Voxelindices = *Voxelindicess;
			const std::vector<short>& ChunkField = ChunkFound->GetChunkFields();
			std::vector<Vec3> VoxelsWhereTheCharacterStays;
			int Height = 0;
			for (int i = 0; i < ChunkDimensionsLength; i++)
			{
				int VoxelCordsIndex = std::find(VoxelPos.begin(), VoxelPos.end(), (Vec3(float(std::round(EndLocation.X)), (float)i, float(std::round(EndLocation.Z))))) - VoxelPos.begin();
				Vec3 Cord = VoxelPos[VoxelCordsIndex];
				if (0 < ChunkField[Voxelindices[VoxelCordsIndex]])
					VoxelsWhereTheCharacterStays.push_back(Cord);
			}
			for (int i = 0; i < (int)VoxelsWhereTheCharacterStays.size(); i++)
			{
				if (VoxelsWhereTheCharacterStays[i].Y > Height)
					Height = (int)VoxelsWhereTheCharacterStays[i].Y;
			}
			if (VoxelCords != ChunkTotalElements) { EntityPosY = (Height + 2); break; }
		}
		else
		{
			break;
		}
	}
}