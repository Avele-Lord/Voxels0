#include "MobManager.h"


MobManager::MobManager() // may be i will pass some parameters in consturctor
{
	// SO manager have to init itself (if there is somthing to init)
	CreateAndInitAllMobSystems(); // mainly it iwll init systems
	// we wont init and creat any comps or mobs here COS well we dont have any in our game spowned yet
}

MobManager::~MobManager()
{
	// well here i destory all alocated memory etc 
}

void MobManager::CreateAndInitAllMobSystems()
{
	// NOW QUESITION IS first of all DATA I DONT PORABBBLY NEED DATA systems have NO FREAKIGN DATA
	// NOW i probbably or init it with ID or with i dont even know but tere is litlte to init stuff in systems
	// RENDERSYSTEM.Init(DATA);
	// TRANSFORMSYSTEM.Init(DATA);
	// AISYSTEM.Init(DATA);
	// SOUNDSYSTEM.Init(DATA);

}

void MobManager::Update(float DeltaTime)
{
	//RENDERSYSTEM.Update(DeltaTime);
	//TRANSFOMRSYSTEM.Update(DeltaTime);
	//AISYSTEM.Update(DeltaTime);
	//MOVESYSTEM.Update(DeltaTime);
	//COLISIONSAYSTEM.Update(DeltaTime);
}







///////////////////////////////////
// represents "main.cpp" file // START
///////////////////////////////////
//#include "Application"
//#include <chrono>
//#include <thread>
//
//using namespace std::chrono_literals;
//
//void RunUpdate(Application& App)
//{
//	App.Update(33.3f);
//	std::this_thread::sleep_for(500ms);
//}
//
//int main()
//{
//	Application App;
//	App.Init();
//
//	RunUpdate(App);
//	RunUpdate(App);
//	RunUpdate(App);
//
//	system("pause");
//	return 0;
//}
///////////////////////////////////
// represents "main.cpp" file // END
///////////////////////////////////



///////////////////////////////////
// represents "Application.h" file // START
///////////////////////////////////
//#pragma once
//#include "New2023MobManager.h"
//
//
//class Application
//{
//public:
//	bool Init();
//	void Update(float DeltaMS);
//
//private:
//	New2023MobManager MobManager_M;
//};
///////////////////////////////////
// represents "Application.h" file // END
///////////////////////////////////





///////////////////////////////////
// represents "Application.cpp" file // START
///////////////////////////////////
//#include "Application.h"
//
//bool Application::Init()
//{
//	return MobManager_M.Init();
//}
//
//void Application::Update(float DeltaMS)
//{
//	// TODO: time stuff
//
//	MobManager_M.Update(DeltaMS);
//}
///////////////////////////////////
// represents "Application.cpp" file // END
///////////////////////////////////


