#pragma once
// Refactored 20.06.2021	// Looked Through 15.09.2021
#include "Window.h" // need
#include "VoxelWorld.h" // need
#include "God.h" // need
#include "SmallTimer.h" // need
#include "ImguiManager.h" // need
#include "Camera.h" // need
#include "OOMobManager.h" //  I HOPE IT'S NEEDED BUT I DON;T KNOW REALY


//Factor out this class in other classes and in here i want only very simple and easy to use main game loop
class Voxels
{
public:
	Voxels();
	// Master frame / Message loop
	int Go();
	~Voxels() = default;
protected:

private:
	void DoFrame();
	void ShowRawInputWindow();
	void CollectBlock();
	void CollectBlockDelay();
	void CollectBlockDelayNew();


public:
	
protected:

private:
	ImguiManager Imgui;// ImguiManager has to be initialized FIRST or crash!
	OOMobManager TheMobManager;
	class Window Wnd;
	class Camera Cam;
	/// Don't forget to check what with rendering on the edges of the world by fixing world pos so it doesn't generate new chunks(basicly make generate world not on playe pos then fly to the edges and check how renderer works)
	VoxelWorld VoxelWorld;
	std::shared_ptr<std::vector<class Zombie>> Zombies;
	God God;
	SmallTimer Timer;
	SmallTimer TimerDigging;
	Vec3 PointToMoveTo;
	float SpeedFactor = /*1.0f*/ 10.0f/*30.0f*/;
	float BlockToSet = 1;
	float DigAnimationTime = 1.0; // i need to make shure that 1.0 COUNTS AS ONE SECOND 
	int BlockDestroyDelay = 0;
	int DigDamage = /*160*/10;
	bool FlyingMode = true;
	bool IsFinished = false;
	bool ShowDemoWindow = false;

	/// VoxelTypes inventory
	int Snow = 0;
	int Grass = 0;
	int Dirt = 0;
	int Stone = 0;
	int HotStone = 0;
	int EvilStone = 0;
};