#pragma once
#include "OOMobSystem.h"
#include "OOMobComponent.h"
#include "OOMob.h"
#include "MobSystemTypes.h"
#include <vector>
#include <unordered_map>



// dude OO STANDS FOR OLD OLD so eveyrhting with prefix OO cos it's my old and old old ECS versions




















// REWATCH ALL Entity Component System #1-#6 TUTORIAL FORM chanal " Rez Bot " 

/// DUDE bad nuws for you YOU WILL HAVE TO READ ALL COPMOENTS in ALL ECS files which you wrote COS LIKE 50% OF EM no bout some bug BUT INSTED some REALY UNIQUE IMPELMENTATION OR FITURE WHICH I didn't wrote anywhere else SO YOU WILL HAVE TO ACTUALY READ EM EACH COPMMENT
///(may be not idealy BUT FOR REALY READ AND WHOLE COMMENT NOT ONLY FIRST TWO WORDS COS somthing improtnt can be in the middle or at the end!!!


//it's OK to liek for eahc new mob CLASS do some boring the same stuff BUT for each object of mob I WILL NO WAY DO SOME BORING MANUAL HTING IT'S ALL MUUUST BE AUTOMATICK cos i may have throusends and htorusends of mobs change destoring and creating every second!!! 

////////^&^%&***********(((((((((((
////////^&^%&***********(((((((((((
//make Com variables and Funk variables in mobs(basicly one varibalews reprisents compoentns and hitsg mobns comsist of other variables reprisents fucnitons of mob and things whic mob does basicly can do and etc)
// cos again i wanan somehow show and showcase WHAT MOB consist of(what it is) AND what mob can do  hense for first i need compoentns for second i need functions (or yeah i can make basickly variables whic i call funcitons and i dont' have to make actual funcitons!! ) 
////////^&^%&***********(((((((((((
////////^&^%&***********(((((((((((

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// 5 if you thihnk about it WITH ECS i'm alredy not gonna have like sword and gun(GunComponent) and bow INSATED just WeaponComponent HENSE it whoudl nto be logicle to have like SwerlingJumpAtackSystem or EnergyLazerAtackSystem INSTED JUST AtackSystem
//&&&&&&&&&&&&&&&&
/// 5.1( CONTINUE 5TH!!!!) DUDE ileborate on this one (on 5th entry) COS THERE IS SOME TRUETH IN THIS SO CONTINUE THIS        CONTINUE!!!!!!!!
// 5.2 SO hee is the deal I WANNA have not weapon but guin and bow AND not atack but sworling hit etc HENSE THOES THINGS ARE SOME INHERETED CLASSES
// 5.2.1 but how ti implment thoes inhereted claases i don't know or i just inheret some swerling atacks form systems OR i will have atack component which i pass to atack system
// 5.2.2 and thne question is like gun IS IT just copmoent class which i derived from weapon copmonent OOOOR it's a MOOOOB class whic is derived from mob class  ANS it holads may be wepon component
// 5.2.2.1 OOOR may be my gun which is a mob class WILL NOT HAVE just a weapon compoentn inside it INSTED it will consist of helth damage power and other stats of the weapon
// 5.2.2.2 OOOOR i may be make weapon compoentn JUST AS gathering of copmoentn like damage and helth and other stats AND from that weapon compoent I WILOL DERIVE ALL OTHER WEAPON CLASSES liek gun!!!!!!!!!!
//!!!!!!!!!!!!!
//!!!!!!!!!!!!!
//!!!!!!!!!!!!!
// 5.3 i know only one thing which i want 100% IS THAT swerling hit(it's type of atack whihc is basicly like system ) AND  bow(it's type of weapon compoennt) BOTH OF EM whoudl be complytly seporet classes HOW they are made or derived i dont' care BUT I WANNA SEPORET CLASSES!!! so i can see my game!!! 
//!!!!!!!!!!!!!
//!!!!!!!!!!!!!
//!!!!!!!!!!!!!
// 6 I WILL make in skeleton(and all other mobs) calls to Systems to there amin fucntions
// 6.1 and to do this i will need to make overLOADED versions of thoes system functions 
// 6.1.1 AND MAKE EM ALL OR STATICK or just hold reference to needed systems in skeleton
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
// 7 i will have my liek skeleton etc AND OTHER MOBS consist of NOT JUST COMPOENTS but fomr other mobs LIEK skeleton will consist of mob BOW(whih is a weapon copmoent basicly)!! and the Mob Fast shooting (whihc is a ataccking system)
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&
// 8 DO it  has been decided NO long hierercy( ONLY ONE LEVEL HIERARCY!) for compoentns OR systems i have one base class system or compoentn AND DERIVE FOMR IT only at one level like render system or weapon compeontn AND NOT like TopologyRenderSystem derived form render system or GunCompoentn derived from weapon compoentnt( ONLY ONE LEVEL HIERARCY!)
// 8.1 HENSE my gun and swerling hit WILL BE JUST MOBS now i've the porblem of heving insted of ONLY ocmpoentns inside each mob ALSO OTHER MOBS AND A LOT OF EM INSIDE OTHER MOBS which in there turn will have toehr mobs inside em and thoes have otherm obs inside em ONLYT ONLY LIEK 5TH OR 10TH OR EVEN LATER WILL HAVE ACTUAL CONCRET COPMOENTN LIEK weapon compoent inside em!!!
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// i wanna somwhere in anaywhere realy when spawnidng mobs NOT ONLY just span randome mobs BUT ALSO I WILL NEED TO randomeze there weapons and armor and items hwich they have
// 1.1 BUT i also will need not just to randomzed compltylty at randome for mobs weapon and iterms and aromr etc I WILL NEED to like may be insdie each mob itself the items it usualy have and wepoa it usualy have AND what % of different weapon that mob usualy will be given by randomised plus liek 1% thta rnadomiser give the mob wepoan and item or armor NOT from mom's list of weapons and items (so example skeleton has 70% chanes on bow 29% on giving sword by randomiser and each mob also given 1% on compltylty randome weapon SO when i spawn skeleon 70% he gtes bow 29% sword and 1% ANY OTHER WEAPON!) 
// 1.2 i wanan list of usual weapon probably inside of mobs itself 
// 1.3 alspo some mobs wil have 1% on complyt randome wepona some bbigger or smaller liek 3% or 0.5% etc

/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
// I'M FOR REAL all your ECS will be MCS so ""Mob Component System"" NO ENTITIES ON MY WATCH  ALL WILL BE MOBS
// ALL WILL BE MOBS
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////////////////////////


//1.1*** with ECS you can have INCREDEBLE NUMBER OF OJECT like 100, 000 or even 1, 000, 000 or even MORE
//2 * ** in MYECS i wll have
//2.1*** speed of original ECS
//2.2*** also OOP with hierarcy modle FOR coupling and big code reuse when needed
//2.2.1*** AND ALSO for seeing ALL what particualr entity(like zomby) consiste of(variable basicly) and what can do(fucntions)
//2.3*** AND OFCORES component modle  FOR decoupling and modulerety when needed to don't make crazy ilogicle inheratence AND OCORES eveyrhting anywas will consist of components


//////////MY ECS ////   start///////////
//////////MY ECS ////   end///////////
//////////ORIGINAL ECS ////   start///////////
//////////ORIGINAL ECS ////   end///////////





//////////MY ECS ////   start///////////


 
// 1: ok so with vectors of compoentns IT'S a bit harder than a though BUT basicly I PROBABLY will have to do some mix of
// 1.1: mix of white list of BASICLY spaces of memory which alredy destry entityes so thoes compoentns ate also usles and i just will put new components on thoes places (JUST overate data and entitiy ID on compoentnt and call it new compoentn)
// 1.2: and ALSO i will need some system FOR CLEANING actualy like WHEN it's WAYYY to many destroid compoentns I WILL NEED to shrink that vector so ALL basicly destorid data whoudl not take up RAM (like if HALF of compoentns are basicly destory i will need cleaning
// 1.2.1: OR if IN THE MIDDLE tgere are too many destorid compoentns OR EVEN WOERS it's spreded like one copmoent not destorid then 3 destorid thne 1 not destorid DUDE CPU PREFECTHER WON'T LOVE IT 
// 1.2.2: SO i willneed somthing like basicly some compoentnt index inside compoentn tracker SO BASICLY when component changes it's index in vector I WHOUDL ACTUALY OVERIDE IT'S INDEX OF COMPONENT on new and corect once SEEMS prity hard to do BUT ACTUALY it ain that hard I JUST HOPE that IT WON'T BE TOO JAVE ON CPU or whatever else on RAM BASICLY SO IT WHPOUDL BE FAST AND NOW SLOW! 
// 2 MAY BE isted of std::vector of copmoentns i wil use just C array for it COS if i will need to somthin gmore sufisticated with componetns it will be easer to udnerstand and do with usual C arrays 
//



// i shoudl put this code somwhere in main app cpp ( i mean Voxels.cpp)  /// start
// Application app;
// app.Init();
// app.Update();
// i shoudl put this code somwhere in main app cpp ( i mean Voxels.cpp)  /// end

// write may be this app class if needed and make new .h and .cpp file for it! //// start
/// Application.h
// #pragma once
//#include "OOMobManager.h"


//class Application 
//{
//public:
//	bool Init();
//	void Update(float DeltaTime);



//private:
//	OOMobManager MobManager;
//};

/// Application.cpp
// #include "Application.h"
// 
//
//bool Application::Init()
//{
//	return MobManager.Init();
//}
//
//void Application::Update(float DeltaTime)
//{
// TODO : time stuff

//	MobManager.Update(DeltaTime);
//}
//	
// write may be this app class if needed and make new .h and .cpp file for it! //// end



class OOMobComponent;
class OOBaseMobSystem;
class RenderableComponent;
class TransformComponent;

class OOMobManager
{
	//using MobsTD = std::unordered_map<MobIdTD, OOMob>; // check is it corect hash map??? // these are the all mobs for real like vectoro nly hash map
	using MobSystemsTD = std::vector<OOMobSystem*>; // should be using MobSystemsTD = std::vector<OOBaseMobSystem*>;
public:
	OOMobManager();
	~OOMobManager();
	OOMobManager(const OOMobManager&) = delete;
	OOMobManager& operator=(const OOMobManager&) = delete;
	OOMobManager(OOMobManager&&) = delete;
	OOMobManager& operator=(OOMobManager&&) = delete;
	void CreateSystems(); // DUDE i actualy will have to create BASICLY each system manyaly AND ACTUALY new it withy pointer from RAM memory AND put it in allsystems vector AND DO IT FOR EACH  system i have in game (so liek AT LEAST 100 systems!!!)
	void AddMob(OOMob* MobIn); // CreateMob(); // probably i will creta mobs outside in some other vectors
	//void DestroyMob(MobIdTD MobId); // probably i will destroy mobs outside in some other vectors
	bool Init();
	void Update(float DeltaTime);
	OOMobComponent* AddComponentToArrayOfComps(MobComponentTypes MobComponentType/*OOMobComponent&*//*OOR it wil just take compoentn type COS i dont' have compoent YET to add it somwhere!!! */);
	MobIdTD CalculateMobId();



private:



public:
	std::vector<RenderableComponent> AllRenderableComponents;
	std::vector<TransformComponent> AllTransformComponents;
	//std::vector<SomeMobComponent3> Component3s;
	//std::vector<std::vector<OOMobComponent*>*> llllAllComponents;
	std::vector<MobComponentTypes> EnumsForAllComponentVectors; // it's alredy don't needed // I WANNA rifector it latter on somthing like std::list or WHATEVER other datat strucutre swhich cna whole ANYTHING without nay specification AT ALL but i just implement this for fun!!
	std::vector<void*> AllComponentVectors; // it's alredy don't needed // I WANNA rifector it latter on somthing like std::list or WHATEVER other datat strucutre swhich cna whole ANYTHING without nay specification AT ALL but i just implement this for fun!!



private:
	std::vector<OOMob*> Mobs;  //  probably do pointer to mob  //std::vector<OOMob> Mobs;
	MobSystemsTD AllMobSystems;
	//MobsTD Mobs; // check is it corect hash map??? // these are the all mobs for real like vectoro nly hash map
	//OOMobComponent* AddComponent(/*OOMobComponent&*//*OOR it wil just take compoentn type COS i dont' have compoent YET to add it somwhere!!! */);



private:
	MobIdTD MobIdCounter; 
	MobIdTD AddMobAndGetRef(/*IT WILL take mob as an argument OR i don't know */);
	//OOMobComponent* AddComponent(/*OOMobComponent&*//*OOR it wil just take compoentn type COS i dont' have compoent YET to add it somwhere!!! */);
};





//////////MY ECS ////   end///////////








//////////ORIGINAL ECS ////   start///////////
//
//
//// i shoudl put this code somwhere in main app cpp ( i mean Voxels.cpp)  /// start
//// Application app;
//// app.Init();
//// app.Update();
//// i shoudl put this code somwhere in main app cpp ( i mean Voxels.cpp)  /// end
//
//// write may be this app class if needed and make new .h and .cpp file for it! //// start
///// Application.h
//// #pragma once
////#include "OOMobManager.h"
//
//
////class Application 
////{
////public:
////	bool Init();
////	void Update(float DeltaTime);
//
//
//
////private:
////	OOMobManager MobManager;
////};
//
///// Application.cpp
//// #include "Application.h"
//// 
////
////bool Application::Init()
////{
////	return MobManager.Init();
////}
////
////void Application::Update(float DeltaTime)
////{
//// TODO : time stuff
//
////	MobManager.Update(DeltaTime);
////}
////	
//// write may be this app class if needed and make new .h and .cpp file for it! //// end
//
//
//
//class OOMobComponent;
//class OOBaseMobSystem;
//
//class OOMobManager
//{
//	//using MobsTD = std::unordered_map<MobIdTD, OOMob>; // check is it corect hash map??? // these are the all mobs for real like vectoro nly hash map
//	using MobSystemsTD = std::vector<OOMobSystem*>; // should be using MobSystemsTD = std::vector<OOBaseMobSystem*>;
//public:
//	OOMobManager();
//	~OOMobManager();
//	OOMobManager(const OOMobManager&) = delete;
//	OOMobManager& operator=(const OOMobManager&) = delete;
//	OOMobManager(OOMobManager&&) = delete;
//	OOMobManager& operator=(OOMobManager&&) = delete;
//	void CreateSystems();
//	MobIdTD CreateMob();
//	void DestroyMob(MobIdTD MobId);
//	bool Init();
//	void Update(float DeltaTime);
//
//
//
//private:
//	//std::vector<OOMob> Mobs;
//	//std::vector<SomeMobComponent1> Component1s;
//	//std::vector<SomeMobComponent2> Component2s;
//	//std::vector<SomeMobComponent3> Component3s;
//	MobSystemsTD AllMobSystems;
//	//MobsTD Mobs; // check is it corect hash map??? // these are the all mobs for real like vectoro nly hash map
//};

//////////ORIGINAL ECS ////   end///////////