//#include "New2023MobManager.h"

//
//New2023MobManager::New2023MobManager()
//{
//	// TODO: Temp -> Create some test things
//}
//
//New2023MobManager::~New2023MobManager()
//{
//	// here we desttroy all compontnes all vectors of copemotns all compeontns pool 
// // also destory systems and etc
// // also desotyr entities
//}
//
//bool New2023MobManager::Init()
//{
//	//
//}
//
//void New2023MobManager::CreateMobSystems()
//{
//	// creates all systems in the game
//}
//
////void New2023MobManager::Update(float DeltaTime)
////{
////	//
////}
//
//MobID_TD New2023MobManager::CreateMob()
//{
//	return 0;
//}
//
//void New2023MobManager::DestroyMob(MobID_TD MobID)
//{
//	//
//}








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


