// Refactored 20.06.2021(NON Refactored)	// Looked Through 15.09.2021
#include "Voxels.h" // need
#include "imgui/imgui.h" // need
#include "Zombie.h" // need
#include <random> // need
//#include "Block.h"
#include "AllBlocks.h"
#include "OOSkeleton.h"



namespace dx = DirectX;
//Factor out this class in other classes and in here i want only very simple and easy to use main game loop
Voxels::Voxels()
	:
	Wnd(1920, 1080, "Voxels"),
	VoxelWorld(Wnd, Cam),
	Zombies(std::make_shared<std::vector<Zombie>>()),
	God(Zombies, Cam)
{
	// ECS area start
	TheMobManager.Init();
	OOMob::InitTheMobManager(&TheMobManager);
	OOSkeleton MySkeleton; // cool cool now just coupla small htinsg left i just need to AUTOMISE IT SO IT WHOUDL PUT ALL COMPOENTNS OF SKELETON IN VECTORS OF COMPOENENTS CREATE MOBS LIEK WEPAON INSIDE OF SKELEON AND PUT THERE COMPOENTNS IN COMPOENENTS VECTORS AND PUT ALL OF THOES MOS AND SKELETON ITSELF IN MOB VECTOR OF POINTERS AND PORBABLY DO LIEK THROUSEND OF OTHER INITIALIZING HTINGS SO YEAH EASY THINGS A BIT OF EM SHURE!
	OOSkeleton* pp = &MySkeleton;// TEST DELET 

	// ECS area end
	AllBlocksInitG();
// Dope 1000000 cubes start
	Zombie::Initialize(Zombies);
	int i = 0;
	for (int x = 0; x < /*100*/10; x++)
	{
		for (int z = 0; z < /*100*/10; z++)
		{
			for (int y = 0; y < /*100*/10; y++)
			{
				// DELETE THIS LINE IS JSUT FOR TES//Zombies->emplace_back(Zombie(Wnd.Gfx(), Vec3(4328.0f /*+(x * /* origin 25*//*3)*/, 630.0f /*+( y * /*25*//*3)*/, 2013.0f /*+(z * /*25*//*3)*/)));
				Zombies->emplace_back(Zombie(Wnd.Gfx(), Vec3(4328.0f +(x * /* origin 25*/3), 630.0f +( y * /*25*/3), 2013.0f +(z * /*25*/3))));
				i++;
			}
		}
	}
//Dope 1000000 cubes end
	Wnd.Gfx().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 3000.0f)); // Last parameter changing the draw distance 	
}

void Voxels::DoFrame()
{
	/// JUST TEST DELET IT COMPLYTLY /// START
	//std::vector<int> Vecl = { 3,5,8 };
	//auto s = Vecl.data();
	//Vecl.clear();
	//Vecl.emplace_back(5);
	//Vecl.emplace_back(5);
	//Vecl.emplace_back(7);
	//int sd = Vecl.size();
	//Vecl.clear();
	//Vecl.resize(sd+1);

	//std::vector<int> Vecl2 = { 10, 15,144,1221,97,77,58 };
	////std::vector<int> Vecl3 = ;
	////Vecl.insert(Vecl.end(), Vecl2.begin(), Vecl2.end());
	////Vecl.emplace(Vecl.end(), Vecl2[1]);
	//std::vector<int> Vecl3 = std::vector<int>(Vecl.begin(), Vecl.end());
	//Vecl3.insert(Vecl3.end(), Vecl2.begin(), Vecl2.end());
	/// JUST TEST DELET IT COMPLYTLY /// END







	///////MY MATH APP START//////////



	std::uniform_int_distribution<int> NumberOfOre(-1000, 100);
	//std::uniform_int_distribution<int> RandomOre(1, 6); 
	std::random_device OreSeed;
	std::mt19937 OreRandomNumberGenerator(OreSeed());
	std::vector<int> RandomMath;
	RandomMath.resize(10);
	for (int i = 0; i < RandomMath.size(); i++)
	{
		//int RandomNumberR = NumberOfOre(OreRandomNumberGenerator);
		RandomMath[i] = NumberOfOre(OreRandomNumberGenerator);

	//	std::sort(RandomMath.begin(), RandomMath.end());
	}
	std::sort(RandomMath.begin(), RandomMath.end());


	//FUNCITON FOR RULE
	// CUT HTIS FUNCTION OUT| start!!!!
	// int Rule(int x, int y, int z, int w)
	//{
	//return (z / 10 + w / 10)(2 ^ x) + (z / 10 + w / 10)(2 ^ y);
	//}


		// CUT HTIS FUNCTION OUT end|!!!!
	//	R(x, y, z, w) = (z / 10 + w / 10)(2 ^ x) + (z / 10 + w / 10)(2 ^ y)
	//	x e R | x >= 0 & x <= 10 & x Usefulness
	//	y e R | y >= 0 & y <= 10 & y Importance
	//	z e R | z >= 0 & z <= 10 & z Time
	//	w e R | w >= 0 & w <= 10 & w Difficulty
	//	R : R4->R
	//	thresshold to do somthing(to function evalywate to true) 100 <= points(get 100 or more points)
	//USE THIS RULE NOT ONLY WHEN LEARNIGN OR DOING PROJECT USE IT EVERYWHERE IN LIFE WHEN YOUI DOING WHATEVER OR EVEN WHEN PLUING GAMES!!!


	///////MY MATH APP END//////////




	TheMobManager.Update(5);



	const auto DeltaTime = Timer.Mark() * SpeedFactor;
	Wnd.Gfx().BeginFrame(0.44f, 0.81f, 0.88f);
	Wnd.Gfx().SetCamera(Cam.GetMatrix());

	///  NON Refactored start 15.09.2021
	if (!(Zombies->size() == 0))
	{
		/// When mob take damage make effect thta it change color to see thta it took damage!
		//Zombies->operator[](0).TakeDamage(200); // this line just kills all Zombies one by one over like 20 sec
	}
	DirectX::XMFLOAT3 CamPos = Cam.GetCamPos();
	Vec3 CharacterPor = Vec3(CamPos.x, CamPos.y, CamPos.z);

	///Implement mob spawning every second in rendom places
	for (int i = 0; i < Zombies->size(); i++)
	{
		/// Implement colision on Mobs!!!!!
		/// Implement Mobs Spawning on the Chunkcs cos if they will swpawn of the chunk it's lagging  
	//	Zombies->operator[](i).MoveTo(CharacterPor /*PointToMoveTo*/); // this line moves Zombies to CharacterPor or PointToMoveTo
	}
	///  NON Refactored end 15.09.2021

	VoxelWorld.UpdatePosition_RemoveChuncs_AddChunks(); // Put after BeginFrame

	VoxelWorld.GenerateVoxelWorld();
	Zombie::Draw(Wnd.Gfx());


	//God.ShootAI(Vec3(4308.0f/*ORIGINAL 4328.0f */, 630.0f, 2013.0f));// DELET IT'S JSUT FOR TEST!!!

	/// This while loop will press keys even if Cursor is disabled
	while (const auto Key = Wnd.Keyboard.ReadKey())
	{
		if (!Key->IsPress())
		{
			continue;
		}

		switch (Key->GetCode())
		{
		case VK_ESCAPE:
			if (Wnd.CursorEnabled())
			{
				Wnd.DisableCursor();
				Wnd.Mouse.EnableRaw();
			}
			else
			{
				Wnd.EnableCursor();
				Wnd.Mouse.DisableRaw();
			}
			break;
		case VK_F1: ShowDemoWindow = true;	break;
		case 'E': FlyingMode = FlyingMode ? false : true;	break;
		case 'C': CollectBlock();	break;
		case '5': VoxelWorld.SetBlock(BlockToSet, 255);	break;
		case 'Y': Cam.Reset();  break;
		case 'V': God.Shoot();  break;
		case 'U': God.ShootAI(Vec3(4308.0f/*ORIGINAL 4328.0f */, 630.0f, 2013.0f)); break;// LINE JUST FOR TEST DELET IT !!!!!
		}
	}
	if (!Wnd.CursorEnabled())
	{
		if (Wnd.Keyboard.KeyIsPressed('W'))  Cam.Translate({ 0.0f,0.0f,DeltaTime }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('A'))	Cam.Translate({ -DeltaTime,0.0f,0.0f }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('S'))	Cam.Translate({ 0.0f,0.0f,-DeltaTime }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('D'))	Cam.Translate({ DeltaTime,0.0f,0.0f }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('O'))	Cam.Translate({ 0.0f,DeltaTime,0.0f }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('P'))	Cam.Translate({ 0.0f,-DeltaTime,0.0f }, !FlyingMode);
		if (Wnd.Keyboard.KeyIsPressed('1')) SpeedFactor < /*10.0f*/20.0f ? SpeedFactor += /*0.05f*/0.35f : SpeedFactor = /*10.0f*/20.0f;
		if (Wnd.Keyboard.KeyIsPressed('2')) SpeedFactor > 0.05f ? SpeedFactor -= /*0.05f*/0.35f : SpeedFactor = 0.0f;
		if (Wnd.Keyboard.KeyIsPressed('3')) PointToMoveTo = VoxelWorld.GetRayCollision();
		if (Wnd.Keyboard.KeyIsPressed('X')) CollectBlock();
		if (Wnd.Keyboard.KeyIsPressed('Z')) VoxelWorld.SetBlock(BlockToSet, 255);
		if (Wnd.Keyboard.KeyIsPressed('Q')) { CollectBlockDelay(); }
		if (Wnd.Keyboard.KeyIsPressed('4')) { CollectBlockDelayNew(); }
		if (Wnd.Mouse.LeftIsPressed()) God.Shoot();
		if (Wnd.Keyboard.KeyIsPressed('K')) God.ShootAI(Vec3(4308.0f/*ORIGINAL 4328.0f */, 630.0f, 2013.0f));// LINE JUST FOR TEST DELET IT !!!!!
	}
	if (Wnd.Keyboard.KeyIsPressed('G'))	IsFinished = true;


	while (const auto Delta = Wnd.Mouse.ReadRawDelta())
	{
		if (!Wnd.CursorEnabled())
		{
			Cam.Rotate((float)Delta->x, (float)Delta->y);
		}
	}




	// Imgui window to control simulation speed
	if (ImGui::Begin("Simulation Speed"))
	{
		ImGui::SliderFloat("Speed Factor", &SpeedFactor, 0.0f, 6.0f, "%.4f", 3.2f);
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Status: %s", Wnd.Keyboard.KeyIsPressed(VK_SPACE) ? "PAUSED" : "RUNNING (hold spacebar to pause)");
	}
	ImGui::End();
	// Crosshairs
	ImGui::SetNextWindowPosCenter();
	if (ImGui::Begin("G"))
	{
		ImGui::SetWindowSize(ImVec2(1.0f, 1.0f), 0);
	}
	ImGui::End();
	
	if (ImGui::Begin("Voxels"))
	{
		ImGui::SliderFloat("Snow", &BlockToSet, 1.0f, 1.0f, "%.4f", 3.2f);
		ImGui::SliderFloat("Grass", &BlockToSet, 5.0f, 5.0f, "%.4f", 3.2f);
		ImGui::SliderFloat("Dirt", &BlockToSet, 6.0f, 6.0f, "%.4f", 3.2f);
		ImGui::SliderFloat("Stone", &BlockToSet, 2.0f, 2.0f, "%.4f", 3.2f);
		ImGui::SliderFloat("HotStone", &BlockToSet, 3.0f, 3.0f, "%.4f", 3.2f);
		ImGui::SliderFloat("EvilStone", &BlockToSet, 4.0f, 4.0f, "%.4f", 3.2f);

		ImGui::Text("%.3d Snow", Snow);
		ImGui::Text("%.3d Grass", Grass);
		ImGui::Text("%.3d Dirt", Dirt);
		ImGui::Text("%.3d Stone", Stone);
		ImGui::Text("%.3d HotStone", HotStone);
		ImGui::Text("%.3d EvilStone", EvilStone);
		ImGui::SetWindowSize(ImVec2(200.0f, 300.0f), 0);
	}
	ImGui::End();
	// Imgui windows to control Camera and light
	Cam.SpawnControlWindow();




	if (!FlyingMode)
	{
		dx::XMFLOAT3& CamPos = Cam.GetCamPosRef();
		VoxelWorld.CollisionDetection(CamPos.x, CamPos.y, CamPos.z);
	}


	// Present
	Wnd.Gfx().EndFrame();
}


void Voxels::ShowRawInputWindow()
{
	if (ShowDemoWindow)
	{
		ImGui::ShowDemoWindow(&ShowDemoWindow);
	}
}


int Voxels::Go()
{
	while (true)
	{
		// Process all messages pending, but to not block for new messages
		if (const auto Ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *Ecode;
		}
		if (IsFinished)
		{
			const auto Ecode = Window::ProcessMessages();
			return *Ecode;
		}
		DoFrame();
	}
}


void Voxels::CollectBlock()
{
	int CollectedBlock = VoxelWorld.SetBlock(0, DigDamage);

	// Make enum for block types 
	switch (CollectedBlock)
	{
	case 1:
		Snow++;
		break;
	case 2:
		Stone++;
		break;
	case 3:
		HotStone++;
		break;
	case 4:
		EvilStone++;
		break;
	case 5:
		Grass++;
		break;
	case 6:
		Dirt++;
		break;
	}
}

void Voxels::CollectBlockDelay()
{
	if (60 < BlockDestroyDelay)
	{
		CollectBlock();
		BlockDestroyDelay = 0;
	}
	else
	{
		BlockDestroyDelay++;
	}
}

// make delay USING TIMER!!! so like mak timer go up to 1.5 sec aand stop and IF timer if  equalt to 1.5 sec we set timer to 0 and if timer is less than 1.5 sec we don't dig 
// i need or stop time after it reaches 1.5 to don't go liek to infinity 
// or i need to make two times and it will work for other things!!! 
// It may RIGHT NOW be dipendent on FPS like with 144 fpc it will be more than twice faster digging than with 60 FPS
void Voxels::CollectBlockDelayNew()
{
	if (DigAnimationTime < TimerDigging.Peek())
	{
		CollectBlock();
		TimerDigging.Mark();
	}
}