//////////MY ECS ////   start///////////
#pragma once
#include "OOMobSystem.h"



class RenderableComponent;
class TransformComponent;

class OORenderSystem : public OOMobSystem
{
public:
	OORenderSystem(class OOMobManager* MobManagerP);
	virtual void Update(float DeltaTime) override;
	virtual bool Init() override;
	

	////// test area  start
	OORenderSystem() = delete;
	virtual int TestFunction() override;
	int IntForTesting = 0; // delet it!!! 
	////// tesrt area end
protected:



private:
	//using BaseType = OOMobSystem<RenderableComponent, TransformComponent>;
	//OOMobManager& TheMobManager; // i may be don't need cit at all so delet if dont' needed!!! 
	std::vector<RenderableComponent>& AllRenderableComponents;
	std::vector<TransformComponent>& AllTransformComponents;
	std::vector<CompIndexTD> AllPassedRequirementsRenderableComponentIndexes;// don't forget that these indexes i will need to SOMHOW basicly like mob index 435 if i delet 3 mobs befor it i need to make index 432(WELL ACTUALY i'm nto hsur e IFF i can actualy do it AND EVN IF I NEED TO DO IT AT ALL OR MAY BE IDON'T NEED T OD IT AT ALL OR mayt be  iwiill need to make pointers AND COS OF THAT yeah it's gonna  be as slow as without ECS AT ALL!!!! )(and if it's nt pointer THEN i will may need to overide these indeexes FOR EACH ECISING SYSTEM AND NOT ONLY FOR MOB FOR EACH VECTOR OF SUCH INDEXES BASICLY!!! ) 
	std::vector<CompIndexTD> AllPassedRequirementsTransformComponentIndexes;
};



//////////MY ECS ////   end///////////



















//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


//////////ORIGINAL ECS ////   start///////////

//#pragma once
//#include "OOMobSystem.h"



//class OORenderSystem : public OOMobSystem<RenderableComponent, TransformComponent>
//{
//public:
//	OORenderSystem(OOMobManager* MobManagerP);
//	virtual void Update(float DeltaTime) override;
//
//
//
//protected:
//
//
//
//private:
//	using BaseType = OOMobSystem<RenderableComponent, TransformComponent>;
//};


//////////ORIGINAL ECS ////   end///////////