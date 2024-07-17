#pragma once
#include"MobSystemTypes.h"
#include <vector> // i am not shure THAT IT'S NOT REDUNDENT COS new includes can have vector included alredy in em 





//////////MY ECS ////   start///////////


class OOMob;
enum class MobComponentTypes : unsigned int;
// 1 in .h   have vectos EACH UNIQUE for each system 
// 1.1 and thta vector will contain ALL mating copomnents  INDESIS!!!!!!
// 2 FIRTS goes vectors of requaired compoentns second of opotional compoentns this is my convention
// 3 somtims i iwll need to have like TWO the same compoents as requairment for system to work LIKE TWO WEAPONS! 

class OOMobSystem
{
public:
	explicit OOMobSystem();
	void OnMobCreated(const OOMob& MobIn, std::vector<std::vector<unsigned int>*>&/***//* or std::vector<std::vector<unsigned int>*>   */  AllIndexesOfComponentSystem, std::vector<MobComponentTypes> CallItSomthingLikeAllComponentTypesIDontKnow, std::vector<MobComponentTypes> MobComponentTypesRequired, std::vector<MobComponentTypes> MobComponentTypesOptional);// MAY BE SHOULD BE VIRTUAL oor overLOAD in derived classes ???
	//void OnMobDestroyed(MobIdTD MobIdIn); // MAY BE SHOULD BE VIRTUAL oor overLOAD in derived classes ???
	virtual ~OOMobSystem() = default;  // if i use BaseMobSystem  this function should be only in the BaseMobSystem class and form here i should delete it!!!
	virtual bool Init() = 0;  // WHAT do you mean initialize system WITH WHAT??? cos systems have NO DATA!!!   
	virtual void Update(float DeltaTime/*, Context* ContextP*/) = 0; 

	////// test area  start
	virtual int TestFunction() = 0;
	////// tesrt area end

private:
	/// /////////start/// only for conry momsystems AND each vectors of componmentsa is uniqye for each system1(well somtims the same but you get it ) 
	//std::vector<IndexForSomeMobComponent(i.e RenderableComponentIndec)>RenderableComponentIndecS;

    /// ///////end///// only for conry momsystems AND each vectors of componmentsa is uniqye for each system1(well somtims the same but you get it ) 


protected:


private:
};

 

//////////MY ECS ////   end///////////









//////////ORIGINAL ECS ////   start///////////


//#pragma once
//#include "OOBaseMobSystem.h"// i am not shure THAT IT'S NOT REDUNDENT COS new includes can have vector included alredy in em 
//#include <vector> // i am not shure THAT IT'S NOT REDUNDENT COS new includes can have vector included alredy in em 
//
//
//class OOMob;
//class OOMobManager;
//enum class MobComponentTypes : unsigned int;
//

////template <class... Comps>
//class OOMobSystem : public OOBaseMobSystem
//{
//public:
//	OOMobSystem(OOMobManager* MobManagerP);
//	//virtual void OnMobCreated(const OOMob& MobIn) override final;
//	//virtual void OnMobDestroyed(MobId MobIdIn) override final;
//	virtual ~OOMobSystem() = default;  // if i use BaseMobSystem  this function should be only in the BaseMobSystem class and form here i should delete it!!!
//	virtual bool Init() = 0;  // if i use BaseMobSystem  this function should be only in the BaseMobSystem class and form here i should delete it!!!
//	virtual void Update(float DeltaTime/*, Context* ContextP*/) = 0;  // if i use BaseMobSystem  this function should be only in the BaseMobSystem class and form here i should delete it!!!
//
//
//
//private:
//	// recursivly looks thropught component types
//	//template <size_t Index, class CompType, class... CompArgs>
//	//bool ProcessMobComponent(ComponentId ComponentIdIn, OOMobComponent* ComponentP, CompTuple& TupleToFill);
//	// This is the turmination specalization of the recursion, which happons when we no longer have a CompTuple
//	// That's passed in.
//	//template <size_t Index>
//	//bool ProcessMobComponent(ComponentId ComponentIdIn, OOMobComponent* ComponentP, CompTuple& TupleToFill);
//
//
//protected:
//	//using CompTuple = std::tuple<std::_Add_pointer<Comps>...>; // a tuple of component pointers
//	//std::vector<CompTuple, PooledStdAllocator> Components;
//
//
//	 
//private:
//	//using AMobIdToIndexMap = std::unordered_map<MobId, size_t, std::hash<MobId>, std::equal_to<MobId>/*,PooledStdAllocator*/>;   // is wass from eastl labryry eastl::hash<>  BUUT i use std SO  will thos be correct or not LEARN which one is the same as in eastl but form std std::hash<> (THE SAME learn baout std::equal_to<> (which original is eastl::equal_to
//	//AMobIdToIndexMap MobIdToIndexMap;
//};
//
//

//////////ORIGINAL ECS ////   END///////////
