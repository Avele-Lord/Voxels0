#include "OOMobManager.h"
#include "OORenderSystem.h" // insted of including each system here just make .h with all systems included AND include that .h in here! 
#include "RenderableComponent.h" // insted of including each component here just make .h with all components included AND include that .h in here! 
#include "TransformComponent.h"
//#include ""


//////////MY ECS ////   start///////////




OOMobManager::OOMobManager()
	:
	MobIdCounter(0)
{
	// TODO: Temp -> create some test things
	// TRY TO IMPLEMENT AREA START
 


	// WELL i have several way to implement this(cos i DEFINETLY cannot precompile somthing which you DON'T KNOW the class of!)
	// 1 i can use here HUUUUGE SWITCE STATMENT for each vector of compoentns to jump to that
	// 2 i can make tuple I JUST will have to make tuple on 1000 differen classes in it (or more for each compoentn in game basicly) WHICH MEANS i have to wririte thoes 1000 compoents  in one tuple WHICH IS  not much worsds then switche statment on 1000 lines!
	// 3 MAY BE some linked list OR  other data sturcutre can do what i need and hoald like 1000 different classes ?????
	// 4 THINK OF somthing else!! cos there are PORBBALY MILLION OTHER WAY  to do it better!!!
	/// DUDE you must make a good pick COS if it's bad and hard to maintain and you won't be able to rifector it later YOU WITH THIS BAD THING which hard to mainten FOR GOOD!!! 

	std::vector<OOMobComponent*> SD;
	//std::tuple<> FindVoxels(RayCast& Ray);
	//std::list<int> ok;
  
	// TRY TO IMPLEMENT AREA END
}

OOMobManager::~OOMobManager()
{
	// TODO: destroy ALL components and object of manager(entities systems components etc)
}

// may be i will need some aray of indexes conected with which system index is conected TO index in needed me system when i need 
void OOMobManager::CreateSystems()
{
	// may be i will need some aray of indexes conected with which system index is conected TO index in needed me system when i need 
	AllMobSystems.emplace_back(new OORenderSystem(this));
	//AllMobSystems.emplace_back(new TransformSystem(this));
	// etc 

}

void OOMobManager::AddMob(OOMob* MobIn)
{
	Mobs.emplace_back(MobIn);
	//return CalculateMobId();
	//return MobIdTD(); 
}

//MobIdTD OOMobManager::CreateMob()
//{
//	return MobIdTD(); // or// return 0;
//}
//
//void OOMobManager::DestroyMob(MobIdTD MobId)
//{
//}

bool OOMobManager::Init() // do i even need double stage initializaiton COS i choudl just init it all IN CONSTRUCTOR!!! 
{
	CreateSystems();
	return false;// don;t know about this
}

 

void OOMobManager::Update(float DeltaTime /*,SomeContext MyContext // well Context is BASICLY data some chunk of bytes OR may be componentS???*/)
{
	for (OOMobSystem* MobSystemP : AllMobSystems)
	{
		MobSystemP->Update(DeltaTime/*,SomeContext*/);
	}
}

OOMobComponent* OOMobManager::AddComponentToArrayOfComps(MobComponentTypes MobComponentType)
{
	//1 MAY BE this funciton shoudl ALSO init compoentnts???
	OOMobComponent* CreatedMobComponent = nullptr; 

	switch (MobComponentType)
	{
		case MobComponentTypes::RenderableComponent: {CreatedMobComponent = &(AllRenderableComponents.emplace_back(RenderableComponent(/*some init data rigth here OR PROBABLY init later! */)));	break;}
		//case MobComponentTypes::TransformComponent: {CreatedMobComponent = &(AllRenderableComponents.emplace_back(TransformComponent(/*some init data rigth here OR PROBABLY init later! */)));	break;}
		case MobComponentTypes::TransformComponent: {CreatedMobComponent = &(AllRenderableComponents.emplace_back(RenderableComponent(/*some init data rigth here OR PROBABLY init later! */)));	break;}


	//default:
	//	break;
	} 

	return CreatedMobComponent;
}

MobIdTD OOMobManager::CalculateMobId()
{
	return MobIdCounter++;// is this increses firts and thne resutnr or not COS I NEED FIRTS RETURN and thne increment
}


//////////MY ECS ////   end///////////




//////////ORIGINAL ECS ////   start///////////


//OOMobManager::OOMobManager()
//{
//	// TODO: Temp -> create some test things
//}
//
//OOMobManager::~OOMobManager()
//{
//	// TODO: destroy ALL components and object of manager(entities systems components etc)
//}
//
//void OOMobManager::CreateSystems()
//{
//	// TODO: creat all systems
//}
//
//MobIdTD OOMobManager::CreateMob()
//{
//	return MobIdTD(); // or// return 0;
//}
//
//void OOMobManager::DestroyMob(MobIdTD MobId)
//{
//}
//
//bool OOMobManager::Init()
//{
//	return false;
//}

//void OOMobManager::Update(float DeltaTime)
//{
//	//for each(OOMobSystem* MobSystemP : AllMobSystems)
//	//{
//	//	MobSystemP->Update(DeltaTime/*,SomeContext*/);
//	//}
//}



//////////ORIGINAL ECS ////   end///////////