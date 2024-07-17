// Refactored 28.10.2021	// Looked Through 15.09.2021
#include "ChunkGenerator.h" // need
#include "ConstantsChunkGenerator.h" // need
#include <random> // need
//#include "AllBlocks.h"
#include "Block.h"


// Test is the chunk generation on CPU takes long time or making it on GPU  takes long time
//  Cube parameters
// Make this array ints NOT floats
// Make this static imbedded object
const Vec3 bMask[] = { Vec3(0.000000, 1.000000, 0.000000), Vec3(0.000000,-1.000000, 0.000000), Vec3(0.000000, 0.000000, 1.000000), Vec3(0.000000, 0.000000, -1.000000), Vec3(1.000000, 0.000000, 0.000000), Vec3(-1.000000, 0.000000, 0.000000) }; // Make this array ints NOT floats
extern Block AllBlocks[];

ChunkGenerator::ChunkGenerator(const Vec3 ChunksPos, const int ChunkX, const int ChunkY, const int ChunkZ, Graphics& Gfx)	
	:
	Gfx(Gfx),
	VoxelCoordinates(ChunkTotalElements, ChunkTotalElements),
	ChunkFields(ChunkTotalElements),
	ColorGradients(ChunkTotalElements),
	VoxelsHP(ChunkTotalElements),
	NumberOfVirtualChunkEdges(6),
	AdjacentChunkGenerators(NumberOfVirtualChunkEdges, nullptr),
	AdjacentChunkGeneratorsStates(NumberOfVirtualChunkEdges, AdjacentChunkGeneratorState::AdjacentChunkGeneratorIsNotBound),
	ChunksPos(ChunksPos),
	ChunkXIndex(ChunkX),
	ChunkYIndex(ChunkY),
	ChunkZIndex(ChunkZ),
	VoxelSizeHalf((float)VoxelSize / 2.0f),
	VoxelPosX(ChunkX * ChunkDimensionsLength),
	VoxelPosY(ChunkY * ChunkDimensionsLength),
	VoxelPosZ(ChunkZ * ChunkDimensionsLength),
	ColorGradient(ChunkDimensionsLength / 5),
	ChunkHasBeenGeneratedBool(false)
{
	std::uniform_real_distribution<float> PercentRealDistribution(0, 100); // may be it should be like 1, 100 start form 1 not form 0 
	std::uniform_int_distribution<int> RandomOreType(1, 6); // from 1 cos on 0 i have zero block NO BLOCK BASICLY 
	std::random_device RandomNumberGeneratorSeed;// you need seed to eb different on every chunk OR ALL YOUR TREES and ore will be on every chunk in exect same place and in exect same from BUUT you need to make seed be on every chunk the same atfre relod of chunk or relod of game COS IF NOT you fly back and forth and trees each time iwll spown in different places!
	// make one mt19937 in projetc ANDD REUS IT EVERYWHERE! 
	std::mt19937 RandomNumberGenerator(RandomNumberGeneratorSeed());// to make treas and ore apear each time in the same place after regeneration(basicly work as noise) you just need to make for each chunk unic ID and so every time this chunk is spawn it has the same ID every time and put ID as seed!    // can be one randomgenerator on all project??? LEARN IT 

	// 3D NOISE RIFECTOR START
	int CavesOrMountains;
	if (VoxelPosY < -1000)
	{
		CavesOrMountains = 0;
	}
	else
	{
		CavesOrMountains = 1;
	}

	float XMultFirst = 1.0f;
	float YMultFirst = 1.0f;
	float ZMultFirst = 1.0f;
	float WeightFirst = 1.0f;

	float XMultSecond = 1.0f;
	float YMultSecond = 1.0f;
	float ZMultSecond = 1.0f;
	float WeightSecond = 1.0f;

	float XMultThird = 1.0f;
	float YMultThird = 1.0f;
	float ZMultThird = 1.0f;
	float WeightThird = 1.0f;


	std::vector<FastNoiseLite> Noise3DArray = Noise3DInit();
	FastNoiseLite FastNoiseLite3D = Noise3DArray[0];
	FastNoiseLite FastNoiseLite3DSecond = Noise3DArray[1];
	FastNoiseLite FastNoiseLite3DThird = Noise3DArray[2];
	// 3D NOISE RIFECTOR END

	std::vector<Vec3> TreeCenters;
	const std::vector<int> Noise = CalculateChunkNoise(); // when start using cubic chunks WHNE I IWLL NEED performance i just need to culculet this noise once on each new x and z cords AND DON'T culculate it every time on each y cord COS it's 2D noise and it never change on y cord so just don't culculate it cos you iwll get the same result all the time on differen y cord
	int VoxelIndex = 0;

	for (int x = 0; x < ChunkDimensionsLength; x++)
	{
		for (int z = 0; z < ChunkDimensionsLength; z++) 
		{
			for (int y = 0; y < ChunkDimensionsLength; y++) 
			{
				int Index = x + (z *  ChunkDimensionsLength) + (y *  ChunkSliceElements);
			
				VoxelCoordinates.first[VoxelIndex].X = float(VoxelPosX + x);
				VoxelCoordinates.first[VoxelIndex].Y = float(VoxelPosY + y); 
				VoxelCoordinates.first[VoxelIndex].Z = float(VoxelPosZ + z);
				VoxelCoordinates.second[VoxelIndex] = Index; // i think may be you chould have done this without this VoxelCoordinates array at all LIKE just indexing directly into the arra of voxel feals DON'T KNOW THO may be not

				ColorGradients[Index] = (std::abs(VoxelPosY) + y) % ColorGradient;
					

				if ((VoxelPosY + y) < 31 + Noise[x + z * ChunkDimensionsLength])
				{
					if ((VoxelPosY + y) == 30 + Noise[x + z * ChunkDimensionsLength]) ChunkFields[Index] = 5;
					else if ((VoxelPosY + y) == 29 + Noise[x + z * ChunkDimensionsLength]) ChunkFields[Index] = 6;
					else if ((VoxelPosY + y) <= 50) ChunkFields[Index] = 4;
					else if ((VoxelPosY + y) <= 100) ChunkFields[Index] = 3;
					else if ((VoxelPosY + y) <= 150) ChunkFields[Index] = 2;
					else if ((VoxelPosY + y) <= 210) ChunkFields[Index] = 1;
					else if ((VoxelPosY + y) <= 9999999) ChunkFields[Index] = 1;
				}
				//THIS WAS COMENTID OUT BEFOR CUBIC CHUNKS DO NOT COMENT THIS OUT IT'S WELL PORBABLY NOT GONNA WORK //else ChunkFields[Index] = 0; // I probably can delete this line cos all the ChunkFields all zeroed out anyways but for safety better be just commented out


				// 3D NOISE START
				if (0.35 < (WeightThird * FastNoiseLite3DSecond.GetNoise((float)((VoxelPosX + x) * XMultThird), (float)((VoxelPosY + y) * YMultThird), (float)((VoxelPosZ + z) * ZMultThird))))
				{
					ChunkFields[Index] = CavesOrMountains;
				}

				if (0.55 < (WeightSecond * FastNoiseLite3D.GetNoise((float)((VoxelPosX + x) * XMultSecond), (float)((VoxelPosY + y) * YMultSecond), (float)((VoxelPosZ + z) * ZMultSecond))))
				{
					ChunkFields[Index] = 0;
				}
			
				if (ChunkFields[Index] != 0)
				{
					if (0.65 < (WeightFirst * FastNoiseLite3DThird.GetNoise((float)((VoxelPosX + x) * XMultFirst), (float)((VoxelPosY + y) * YMultFirst), (float)((VoxelPosZ + z) * ZMultFirst))))
					{
						ChunkFields[Index] = 3;
					}
				}
				// 3D NOISE END

				// trees
				if (PercentRealDistribution(RandomNumberGenerator) < 2.0 && (VoxelPosY + y) == 31 + Noise[x + z * ChunkDimensionsLength])
				{
					TreeCenters.emplace_back(Vec3(x, y, z));
				}
				// trees


				float ChanceToSpawnAnOre = PercentRealDistribution(RandomNumberGenerator);
				if (ChanceToSpawnAnOre < 0.005 && 0 != ChunkFields[Index]) // && 0 != ChunkFields[Index] Comment out this to check how many ores spawns
				{
					int RandomOreTypeNumber = RandomOreType(RandomNumberGenerator);
					for (int i = -5; i < 0; i++)
					{
						for (int k = -5; k < 0; k++)
						{
							for (int j = -5; j < 0; j++)
							{
								/// DON'T COMENT THIS LINE OUT IT'S USEFUL! IT'S MY ORE IN THE WORLD! 
								if (ChunkTotalElements > (x + i + ((z + k)*  ChunkDimensionsLength) + ((y + j) * ChunkSliceElements)) && 0 <= (x + i + ((z + k)*  ChunkDimensionsLength) + ((y + j) * ChunkSliceElements))) // delete htis if statmen later cos it's uneeded just without it game crashes! 
								{
									int IndexInner = (x + i + ((z + k)*  ChunkDimensionsLength) + ((y + j) * ChunkSliceElements));
									ChunkFields[IndexInner] = /*0*//*100*/RandomOreTypeNumber; // 0 dopest debug check and 100 also good for debuging
									VoxelsHP[IndexInner] = AllBlocks[ChunkFields[IndexInner]].GetHP();
								}
							}
						}
					}
				}
				VoxelsHP[Index] = AllBlocks[ChunkFields[Index]].GetHP(); // mind you THAT HERE A HUGE BUG cos like look trees AND ore will have ABSOLUTLY WRONG HP or may be ownt' have HP AT ALL cos trees and ore blocks will apyer AFTER i init HP OR FOR ORE may be evne befor i init HP SO any ways there will be or no HP or htere will be HP of other block(somtims cna be corect if luckout) NOT GONNA FIX IT cos i wanna reado spawn of trees and ore naywas ) make em spown by noise if possible(i think it's gonnabe hard hto ESPECIALY YOU AIN GONNA spawn vilegies cities basis any building etc with noise!)
				VoxelIndex++;


			}
		}
	}



	////////// Trees start
	// Smaller range for tree - we don't want to spawn them on shared areas or edges
	std::uniform_int_distribution<int> RandomTreeHeight(3, 6);
	std::uniform_int_distribution<int> RandomTreePos(0, 2);

	for (Vec3 TreeCenter : TreeCenters)
	{
		int TreeHeight = RandomTreeHeight(RandomNumberGenerator);
		int RandomX = RandomTreePos(RandomNumberGenerator);
		int RandomY = RandomTreePos(RandomNumberGenerator);
		int RandomZ = RandomTreePos(RandomNumberGenerator);
		
		// Tree Leaves
		for (int TreeX = -2; TreeX < 3; TreeX++)
		{
			for (int TreeY = -2; TreeY < 3; TreeY++)
			{
				for (int TreeZ = -2; TreeZ < 3; TreeZ++)
				{
					if (InRange(TreeX + TreeCenter.X, ChunkDimensionsLength) && InRange(TreeY + TreeCenter.Y, ChunkDimensionsLength) && InRange(TreeZ + TreeCenter.Z, ChunkDimensionsLength))// THI LINE delete later BUUT i did it only cos without this line some treas spown in strange places
					{
						int Index = TreeCenter.X + TreeX + (ChunkSliceElements * (TreeCenter.Y + TreeY + TreeHeight)) + (ChunkDimensionsLength * (TreeCenter.Z + TreeZ));
						if (InRange(Index, ChunkTotalElements))
						{
							float Radius = Vec3(TreeX * RandomX, TreeY * RandomY, TreeZ * RandomZ).GetLength();

							if (Radius <= 2.8)
							{
								if (PercentRealDistribution(RandomNumberGenerator) < 50 || Radius <= 1.2)
								{
									ChunkFields[Index] = 4;
									VoxelsHP[Index] = AllBlocks[ChunkFields[Index]].GetHP(); // i also need to ste hp here and eveyrwhere where i set blocks!
								}
							}
						}
					}
				}
			}
		}

		// Tree Trunk
		for (int h = 0; h < TreeHeight; h++)
		{
			int Index = TreeCenter.X + ((TreeCenter.Y + h) * ChunkSliceElements) + (TreeCenter.Z * ChunkDimensionsLength);
			if (InRange(Index, ChunkTotalElements))
			{
				ChunkFields[Index] = 6;
				VoxelsHP[Index] = AllBlocks[ChunkFields[Index]].GetHP();
			}
		}
	

	}
	////////// Trees end

	//for (int i = 0; i < ChunkFields.size(); i++)
	//{
	//	VoxelsHP[i] = AllBlocks[ChunkFields[i]].GetHP();// COMENT ALL OTEHR FILING HP ARRAI THING AND UNCOMENT THIS HTIS IWLL FEAL IT IN ONE FELL SWOOP!
	//}

/// DON'T YOU EVER DELETE THIS This makes some cool floors each 20 blocks IT'S two worlds cave standart world on bottom AND flipped world on top of standart world AND I GET LIKE nether in minecraft!
//else if (Random == 20) ChunkFields[Index] = 245;

//if (Random == 20)
//{
//	Random = 0;
//}
//Random++;

// X Y Z are flipped start
/////	 DON'T YOU EVER DELETE THIS IT'S TOO COOL TO BE DELETED // START Awesome caves AND Awesome 2D map of the biomes
//	int j = 0;	/// Awesome caves
//	bool DoFloor = true;	/// Awesome caves
//	for (int i = 57; i > 0; i--)	/// Awesome caves
//	{	/// Awesome caves
//		///if (i + Noise[x + y * ChunkDimensionsLength] < 1) 	/// This line of code is awesome 2D map of the biomes 
//		if (z == (i + Noise[x + y * ChunkDimensionsLength]))	/// Awesome caves
//		{	/// Awesome caves
//			ChunkFields[Index] = j;	/// Awesome caves
//			DoFloor = false;	/// Awesome caves
//			break;	/// Awesome caves
//		}	/// Awesome caves
//		j++;	/// Awesome caves
//	}	/// Awesome caves
//	if (DoFloor)	/// Awesome caves
//	{	/// Awesome caves
//		if (z < 1) ChunkFields[Index] = 1;	/// Awesome caves
//		else ChunkFields[Index] = 0;	/// Awesome caves
//	}	/// Awesome caves
//	///	 DON'T YOU EVER DELETE THIS IT'S TOO COOL TO BE DELETED // END  Awesome caves AND Awesome 2D map of the biomes 
// X Y Z are flipped end
}



// Generating Chunk Mesh
//   Tefel Dev,     Unreal Minecraft - Twitch 12h challenge - 2. C++ project set,        Unreal Minecraft - Twitch 12h challenge - 3. Voxel Generation
void ChunkGenerator::GenerateChunk()
{
	/// DUDE I'M ELLING YOU IF SOMTHING DON'T WORK WITH REBDERER or leak of memory IT 50% CXOS OF THTA UNCOMENT IT I JUST DON'T WANNA BUILT IN IT HERE COS IT'S KIND OF NOT COSHER TO CLEAR AND RENDER CHUNK ON ONE FUNCTION // START
	//AChunkMesh.Vertices.clear();
	//AChunkMesh.Indices.clear();
	//AChunkMesh.AChunk.release();
	//AChunkMesh.Colors.clear();
	//AChunkMesh.ColorGradients.clear(); // If delete this line we get dopy waves of color!
	/// DUDE I'M ELLING YOU IF SOMTHING DON'T WORK WITH REBDERER or leak of memory IT 50% CXOS OF THTA UNCOMENT IT I JUST DON'T WANNA BUILT IN IT HERE COS IT'S KIND OF NOT COSHER TO CLEAR AND RENDER CHUNK ON ONE FUNCTION // ENT

	int IndexCount = 0;
	const std::vector<short>& RightAdjacentChunkGenerator = AdjacentChunkGenerators[0]->GetChunkFields();
	const std::vector<short>& LeftAdjacentChunkGenerator = AdjacentChunkGenerators[1]->GetChunkFields();
	const std::vector<short>& TopAdjacentChunkGenerator = AdjacentChunkGenerators[2]->GetChunkFields();
	const std::vector<short>& BottomAdjacentChunkGenerator = AdjacentChunkGenerators[3]->GetChunkFields();
	const std::vector<short>& FrontAdjacentChunkGenerator = AdjacentChunkGenerators[4]->GetChunkFields();
	const std::vector<short>& BackAdjacentChunkGenerator = AdjacentChunkGenerators[5]->GetChunkFields();

	for (int x = 0; x < ChunkDimensionsLength; x++)
	{
		for (int z = 0; z < ChunkDimensionsLength; z++)
		{
			for (int y = 0; y < ChunkDimensionsLength; y++)
			{
				int Index = x + (ChunkDimensionsLength * z) + (ChunkSliceElements * y);
				int MeshIndex = ChunkFields[Index];

				if (MeshIndex > 0)
				{
					MeshIndex--;

					std::vector<BDS::Vertex>& Vertices = AChunkMesh.Vertices;
					std::vector<unsigned short>& Indices = AChunkMesh.Indices;
					std::vector<BDS::Color>& Colors = AChunkMesh.Colors;
					std::vector<BDS::ColorGradient>& ColorGradientsLocal = AChunkMesh.ColorGradients;
					// Add faces, verticies, UVs and normals
					for (int i = 0; i < 6; i++)
					{
						int NewIndex = int(Index + bMask[i].X + (bMask[i].Z * ChunkDimensionsLength) + (bMask[i].Y * ChunkSliceElements));

						bool Flag = false;

						bool IndexingInAdjacentChunkGenerator = false;
						// you can make this if else faster by ordering the fastes if else first then slower second etc
						if (x == 0 && bMask[i].X == -1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (LeftAdjacentChunkGenerator[(ChunkDimensionsLength - 1) + (ChunkDimensionsLength * z) + (ChunkSliceElements * y)] < 1)
							{
								Flag = true;
							}
						}
						else if (x == (ChunkDimensionsLength - 1) && bMask[i].X == 1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (RightAdjacentChunkGenerator[0 + (ChunkDimensionsLength * z) + (ChunkSliceElements * y)] < 1)
							{
								Flag = true;
							}
						}
						else if (y == (ChunkDimensionsLength - 1) && bMask[i].Y == 1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (TopAdjacentChunkGenerator[x + (ChunkDimensionsLength * z) + (ChunkSliceElements * 0)] < 1)
							{
								Flag = true;
							}
						}
						else if (y == 0 && bMask[i].Y == -1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (BottomAdjacentChunkGenerator[x + (ChunkDimensionsLength * z) + (ChunkSliceElements * (ChunkDimensionsLength - 1))] < 1)
							{
								Flag = true;
							}
						}
						else if (z == 0 && bMask[i].Z == -1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (BackAdjacentChunkGenerator[x + (ChunkDimensionsLength * (ChunkDimensionsLength - 1)) + (ChunkSliceElements * y)] < 1)
							{
								Flag = true;
							}
						}
						else if (z == (ChunkDimensionsLength - 1) && bMask[i].Z == 1)
						{
							IndexingInAdjacentChunkGenerator = true;
							if (FrontAdjacentChunkGenerator[x + (ChunkSliceElements * y)] < 1)
							{
								Flag = true;
							}
						}

						// May be even this if statement for translucency(but probably not yeah i think not but who knows)
						if (MeshIndex >= /*20*//*200*/ 400) // Num of voxel types  // For translucency // if block bigger than the valye it means it translusent and we need render block befor or after it // BTW do not delet it cos translucency i will need to do in DX11 ofcores BUT RENDER block bihind traslusent block i will still need to do it! 
						{
							Flag = true; // For translucency  
						}
						else if (NewIndex < (int)ChunkFields.size() && NewIndex >= 0 && !IndexingInAdjacentChunkGenerator) // You can get rid of this else if statment(probably) at least NewIndex < (int)ChunkFields.size()  part
						{
							// This is when mask is checked!!!!! IT'S NOT FOR translucency
							if (ChunkFields[NewIndex] < 1)
							{
								Flag = true;
							}
						}

						if (Flag)
						{ 
							// VoxelSize = 1 don't delet it cos if i change VoxelSize i will need it
							switch (i)
							{
							case 0:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;
								break;
							}
							case 1:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;
								break;
							}
							case 2:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;
								break;
							}
							case 3:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;

								break;
							}
							case 4:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;
								break;
							}
							case 5:
							{
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), -VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), -VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Vertices.emplace_back(BDS::Vertex{ DirectX::XMFLOAT3(-VoxelSizeHalf + (x * VoxelSize), VoxelSizeHalf + (y * VoxelSize), VoxelSizeHalf + (z * VoxelSize)) });
								Indices.emplace_back(0 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(1 + IndexCount);
								Indices.emplace_back(2 + IndexCount);
								Indices.emplace_back(3 + IndexCount);
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								Colors.emplace_back(BDS::Color{ ChunkFields[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								ColorGradientsLocal.emplace_back(BDS::ColorGradient{ ColorGradients[Index] });
								IndexCount += 4;
								break;
							}
							}
						}
					}
				}
			}
		}
	}

	if (!(AChunkMesh.Vertices.size() == 0))
	{
		AChunkMesh.AChunk = std::make_unique<Chunk>(Gfx, ChunksPos.X, ChunksPos.Y, ChunksPos.Z, AChunkMesh.Vertices, AChunkMesh.Indices, AChunkMesh.Colors, AChunkMesh.ColorGradients);
	}
	ChunkHasBeenGeneratedBool = true;
}



std::vector<FastNoiseLite> ChunkGenerator::Noise3DInit()
{
	std::vector<FastNoiseLite> Noise3DArray;


	FastNoiseLite FastNoiseLite3D;

	FastNoiseLite3D.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
	FastNoiseLite3D.SetFractalType(FastNoiseLite::FractalType::FractalType_Ridged); // 1 FractalType_Ridged // 2 // FractalType_PingPong // 3 FractalType_FBm
	FastNoiseLite3D.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan);
	FastNoiseLite3D.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_CellValue);
	FastNoiseLite3D.SetDomainWarpType(FastNoiseLite::DomainWarpType::DomainWarpType_OpenSimplex2);
	FastNoiseLite3D.SetRotationType3D(FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes);// make kave vercicle or horizantle
	FastNoiseLite3D.SetSeed(19937);
	FastNoiseLite3D.SetFrequency(0.015f);
	FastNoiseLite3D.SetFractalOctaves(3);
	FastNoiseLite3D.SetFractalLacunarity(2.0f);
	FastNoiseLite3D.SetFractalWeightedStrength(0.00f);
	FastNoiseLite3D.SetFractalPingPongStrength(0.0f);
	FastNoiseLite3D.SetFractalGain(0.4f);
	FastNoiseLite3D.SetCellularJitter(0.0f);
	FastNoiseLite3D.SetDomainWarpAmp(0.018f);

	Noise3DArray.emplace_back(FastNoiseLite3D);


	FastNoiseLite FastNoiseLite3DSecond;

	FastNoiseLite3DSecond.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
	FastNoiseLite3DSecond.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm); // 1 FractalType_Ridged // 2 // FractalType_PingPong // 3 FractalType_FBm
	FastNoiseLite3DSecond.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan);
	FastNoiseLite3DSecond.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_CellValue);
	FastNoiseLite3DSecond.SetDomainWarpType(FastNoiseLite::DomainWarpType::DomainWarpType_OpenSimplex2);
	FastNoiseLite3DSecond.SetRotationType3D(FastNoiseLite::RotationType3D::RotationType3D_None);// make kave vercicle or horizantle
	//FastNoiseLite3DSecond.SetSeed(19937);
	FastNoiseLite3DSecond.SetFrequency(0.005f);
	FastNoiseLite3DSecond.SetFractalOctaves(3);
	FastNoiseLite3DSecond.SetFractalLacunarity(2.5f);
	FastNoiseLite3DSecond.SetFractalWeightedStrength(0.00f);
	FastNoiseLite3DSecond.SetFractalPingPongStrength(0.0f);
	FastNoiseLite3DSecond.SetFractalGain(0.3f);
	FastNoiseLite3DSecond.SetCellularJitter(0.0f);
	FastNoiseLite3DSecond.SetDomainWarpAmp(0.018f);

	Noise3DArray.emplace_back(FastNoiseLite3DSecond);


	FastNoiseLite FastNoiseLite3DThird;

	FastNoiseLite3DThird.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
	FastNoiseLite3DThird.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm); // 1 FractalType_Ridged // 2 // FractalType_PingPong // 3 FractalType_FBm
	FastNoiseLite3DThird.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan);
	FastNoiseLite3DThird.SetCellularReturnType(FastNoiseLite::CellularReturnType::CellularReturnType_CellValue);
	FastNoiseLite3DThird.SetDomainWarpType(FastNoiseLite::DomainWarpType::DomainWarpType_OpenSimplex2);
	FastNoiseLite3DThird.SetRotationType3D(FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes);// make kave vercicle or horizantle
	FastNoiseLite3DThird.SetSeed(19937);
	FastNoiseLite3DThird.SetFrequency(0.055f);
	FastNoiseLite3DThird.SetFractalOctaves(3);
	FastNoiseLite3DThird.SetFractalLacunarity(2.0f);
	FastNoiseLite3DThird.SetFractalWeightedStrength(0.00f);
	FastNoiseLite3DThird.SetFractalPingPongStrength(0.0f);
	FastNoiseLite3DThird.SetFractalGain(0.4f);
	FastNoiseLite3DThird.SetCellularJitter(0.0f);
	FastNoiseLite3DThird.SetDomainWarpAmp(0.018f);

	Noise3DArray.emplace_back(FastNoiseLite3DThird);


	return Noise3DArray;
}


// Set up Noise Passes
std::vector<int> ChunkGenerator::CalculateChunkNoise() 
{
	NoiseDefault Pass1;
	Pass1.Frequency = 0.00005F;
	Pass1.XMult = 1.05f;
	Pass1.YMult = 1.05f;
	Pass1.Weight = 1200.0f;
	//Pass1.ClampIsOn = true;
	//Pass1.MinClamp = -40.f; //
	//Pass1.MaxClamp = 1000.f;
	NoiseParams.emplace_back(Pass1);

	NoiseDefault Pass2; 
	Pass2.NoiseType = FastNoiseLite::NoiseType::NoiseType_Perlin;
	Pass2.FractalType = FastNoiseLite::FractalType::FractalType_PingPong;
	Pass2.CellularDistanceFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_Manhattan;
	Pass2.CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_CellValue;
	Pass2.DomainWarpType = FastNoiseLite::DomainWarpType::DomainWarpType_BasicGrid;
	Pass2.RotationType3D = FastNoiseLite::RotationType3D::RotationType3D_ImproveXYPlanes;
	Pass2.Seed = 19937;
	Pass2.Frequency = 0.00035F;///
	Pass2.FractalOctaves = 7;
	Pass2.FractalLacunarity = 2.5f;
	Pass2.FractalWeightedStrength = 2.70f;
	Pass2.FractalPingPongStrength = 3.9f;
	Pass2.FractalGain = 0.7f;
	Pass2.CellularJitter = 25.5f;
	Pass2.DomainWarpAmp = 0.018f;
	Pass2.XMult = 1.0f;
	Pass2.YMult = 1.0f;
	Pass2.Weight = 1120.0f;//
	Pass2.ClampIsOn = true;
	Pass2.MinClamp = 120.f; //
	Pass2.MaxClamp = 140.f;

	NoiseParams.emplace_back(Pass2);



	/// First try
	/*NoiseDefault FirstPass;
	FirstPass.XMult = 1.011f;
	FirstPass.YMult = 1.011f;
	FirstPass.Weight = 10.0f;
	NoiseParams.emplace_back(FirstPass);

	NoiseDefault SecondPass;
	SecondPass.Frequency = 0.0021F;
	SecondPass.XMult = 1.011f;
	SecondPass.YMult = 1.011f;
	SecondPass.Weight = 88.0f;
	NoiseParams.emplace_back(SecondPass);

	NoiseDefault ThirdPass; 
	ThirdPass.XMult = 0.001f;
	ThirdPass.YMult = 0.001f;
	ThirdPass.Weight = 24.0f;
	NoiseParams.emplace_back(ThirdPass);

	NoiseDefault FourthPass;
	FourthPass.XMult = 0.004f;
	FourthPass.YMult = 0.004f;
	FourthPass.Weight = 48.0f;
	NoiseParams.emplace_back(FourthPass);

	NoiseDefault FifthPass; 
	FifthPass.XMult = .05f;
	FifthPass.YMult = .05f;
	FifthPass.Weight = 12.0f;
	FifthPass.ClampIsOn = true;
	FifthPass.MinClamp = 0.0f;
	FifthPass.MaxClamp = 5.0f;
	NoiseParams.emplace_back(FifthPass);
*/
	NoiseCalculator NoiseCalculator(ChunkXIndex, ChunkZIndex);
	return NoiseCalculator.CalculateNoise(NoiseParams);
}

		
bool ChunkGenerator::SetVoxel(int VoxelIndexCords, int VoxelToSetTo, int DamageDealtToBlock, int PrevVoxelIndexCords, ChunkGenerator* PrevChunk) // this function can work incorectly with cubick chunks  i mean i may won't be able to put blocks from top and bottom of the chunk on the next chunks!(adgesent chunks)
{
	if (!(VoxelIndexCords == ChunkTotalElements))
	{
		int VoxelIndex = (int)VoxelCoordinates.second[VoxelIndexCords];
		if (!(0 == ChunkFields[VoxelIndex]))
		{
			if (VoxelToSetTo)
			{
				if (PrevChunk)
				{
					PrevChunk->ChunkFields[(int)VoxelCoordinates.second[PrevVoxelIndexCords]] = VoxelToSetTo; // This line for putting blocks ( it actually works don't delete it)
					PrevChunk->VoxelsHP[(int)VoxelCoordinates.second[PrevVoxelIndexCords]] = AllBlocks[VoxelToSetTo].GetHP();  
					PrevChunk->ClearChunkMesh();
					PrevChunk->GenerateChunk();
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				int CurrentVoxelHP = VoxelsHP[VoxelIndex] - DamageDealtToBlock;
				VoxelsHP[VoxelIndex] = CurrentVoxelHP;

				if (0 >= CurrentVoxelHP)
				{
					VoxelsHP[VoxelIndex] = 0; // this line cos when i do  VoxelsHP[VoxelIndex] = CurrentVoxelHP; and i'm alredy inside if statment i will asigne in unsigned chhar  some int valy LIKE 99% OF THE TIME not 0 but like -10 AND in unsigned char is 246 SO i regend HP not damaged it and ofcores there is bug 

					ChunkFields[VoxelIndex] = VoxelToSetTo;
					AChunkMesh.Vertices.clear();
					AChunkMesh.Indices.clear();
					AChunkMesh.AChunk.release();
					AChunkMesh.Colors.clear();
					AChunkMesh.ColorGradients.clear(); // If delete this line we get dopy waves of color!

					GenerateChunk();
				}

				return true;
			}
		}
	}
	return false;
}


// Row pointer DON'T FORGET TO MANAGE DATA DELET AND SET TO NULLPTR OR BAD TIMES!
void ChunkGenerator::BindAdjacentChunkGenerator(ChunkGenerator*  AdjacentChunkGenerator, AdjacentChunkGeneratorState AdjacentChunkGeneratorState)
{
	switch (AdjacentChunkGeneratorState)
	{
	case AdjacentChunkGeneratorState::RightAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[0] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[0] = AdjacentChunkGeneratorState;
		break;
	case AdjacentChunkGeneratorState::LeftAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[1] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[1] = AdjacentChunkGeneratorState;
		break;
	case AdjacentChunkGeneratorState::TopAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[2] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[2] = AdjacentChunkGeneratorState;
		break;
	case AdjacentChunkGeneratorState::BottomAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[3] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[3] = AdjacentChunkGeneratorState;
		break;
	case AdjacentChunkGeneratorState::FrontAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[4] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[4] = AdjacentChunkGeneratorState;
		break;
	case AdjacentChunkGeneratorState::BackAdjacentChunkGeneratorStateIsBound:
		AdjacentChunkGenerators[5] = AdjacentChunkGenerator;
		AdjacentChunkGeneratorsStates[5] = AdjacentChunkGeneratorState;
		break;
	}
}


bool ChunkGenerator::AllAdjacentChunkGeneratorsAreNotEmpty()
{
	for (int i = 0; i < AdjacentChunkGeneratorsStates.size(); i++)
	{
		if (!(AdjacentChunkGenerators[i] == nullptr))
		{
			if (AdjacentChunkGenerators[i]->ChunkFields.size() == 0)
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool ChunkGenerator::AdjacentChunkGeneratorsIsBound(AdjacentChunkGeneratorState AdjacentChunkGeneratorState)
{
	if (AdjacentChunkGeneratorsStates[static_cast<int>(AdjacentChunkGeneratorState)] != AdjacentChunkGeneratorState::AdjacentChunkGeneratorIsNotBound)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// THIS FUNCITON SLOW YOUR GAME THRE TIMES AS SLOW!
/// and it is slow cos i call bunch of funciton calls per second
bool ChunkGenerator::AllAdjacentChunkGeneratorsAreBound()
{
	for (int i = 0; i < AdjacentChunkGeneratorsStates.size(); i++)
	{
		if (AdjacentChunkGeneratorsStates[i] == AdjacentChunkGeneratorState::AdjacentChunkGeneratorIsNotBound)
		{
			return false;
		}
	}
	return true;
}

bool ChunkGenerator::CheckCollisionDetection(int Value)
{
	if (!(Value == ChunkTotalElements))
	{
		if (!(0 == ChunkFields[(int)VoxelCoordinates.second[Value]]))
		{
			return true;
		}
	}
	return false;
}

void ChunkGenerator::ClearChunkMesh()
{
	AChunkMesh.Vertices.clear();
	AChunkMesh.Indices.clear();
	AChunkMesh.AChunk.release();
	AChunkMesh.Colors.clear();
	AChunkMesh.ColorGradients.clear(); // If delete this line we get dopy waves of color!
}

bool ChunkGenerator::InRange(int Value, int Range)
{
	return (Value >= 0 && Value < Range);
}

bool ChunkGenerator::ChunkHasBeenGenerated()
{
	return ChunkHasBeenGeneratedBool;
}

std::vector<short> ChunkGenerator::GetChunkFields() const
{
	return ChunkFields;
}

std::vector<short>& ChunkGenerator::GetChunkFieldsNotConstReference() 
{
	return ChunkFields;
}

std::pair<std::vector<Vec3>, std::vector<int>> ChunkGenerator::GetVoxelPos() const
{
	return VoxelCoordinates;
}

ChunkMesh* ChunkGenerator::GetChunkMesh()
{
	return &AChunkMesh;
}

std::vector<ChunkGenerator*>& ChunkGenerator::GetAdjacentChunkGenerators()
{
	return AdjacentChunkGenerators;
}