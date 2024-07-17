//////////MY ECS ////   start///////////
#include "OORenderSystem.h"
#include "RenderableComponent.h"
#include "TransformComponent.h"
#include "OOMobManager.h"
#include <tuple>


OORenderSystem::OORenderSystem(OOMobManager* MobManagerP) // I PROBABLY WILL NEED MobManager* at least in inhereted classes from MosSystem (in ACTUAL systems!!! ) 
	:
	AllRenderableComponents(MobManagerP->AllRenderableComponents),
	AllTransformComponents(MobManagerP->AllTransformComponents)
{}


void OORenderSystem::Update(float DeltaTime)
{
	//for (auto& CompTuple : Components) // "Components" is variable whioc located in parent class mob system
	//{
	//	TransformComponent* TransformP = std::get<TransformComponent*>(CompTuple);
	//	RenderableComponent* RenderableP = std::get<RenderableComponent*>(CompTuple);

	//	RenderableP->Texture[0] = static_cast<char>(TransformP->Position.X);
	//}
 }

bool OORenderSystem::Init()
{
	return false;
}

int OORenderSystem::TestFunction()
{
	return IntForTesting;
}







//////////MY ECS ////   end///////////



















//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////



//////////ORIGINAL ECS ////   start///////////




//
//#include "OORenderSystem.h"
//#include "TransformComponent.h"
//#include "RenderableComponent.h"
//#include <tuple>


//OORenderSystem::OORenderSystem(OOMobManager* MobManagerP)
//	:
//	BaseType(MobManagerP)
//{}


//void OORenderSystem::Update(float DeltaTime)
//{
//	for (auto& CompTuple : Components) // "Components" is variable whioc located in parent class mob system
//	{
//		TransformComponent* TransformP = std::get<TransformComponent*>(CompTuple);
//		RenderableComponent* RenderableP = std::get<RenderableComponent*>(CompTuple);
//
//		RenderableP->Texture[0] = static_cast<char>(TransformP->Position.X);
//	}
// }



//////////ORIGINAL ECS ////   end///////////