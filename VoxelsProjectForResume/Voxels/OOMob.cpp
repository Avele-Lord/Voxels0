#include "OOMob.h"
#include "OOMobManager.h"



OOMob::OOMob(MobIdTD MobId) // it should NOOOOOOT take MobId !!!!!
	:
	ID(MobId)
{
	TheMobManager->AddMob(this);
	this->ID = TheMobManager->CalculateMobId();
	//MobIdTD ThisMobId = AddThisMobToTheMobManager();
	//ID = ThisMobId;   // make a funciton out of this look pritier OR NOT?? // i will init mob IDs like this AND I WILL NOT PASS IT through the consturctor SO delet mob Id pasing in constructor(i means look above you take mobId  in consturcotr so delet it!)
}

//void OOMob::AddComponent(ComponentId ComponentIdIn, OOMobComponent* MobComponentIn)
//{
//	Components.emplace(ComponentIdIn, MobComponentIn);
//}

//MobIdTD OOMob::GetId() const
//{
//	return ID;
//}

//MobIdTD OOMob::AddThisMobToTheMobManager()
//{
//	return TheMobManager->AddMob(this);
//}
//
//MobIdTD OOMob::CalculateNewIDForMob()
//{
//	return TheMobManager->CalculateMobId();
//}

void OOMob::AddUniqueMobComponents()
{
	// TODO :
	//4.1.3 ALSO THIS WAY IS GOOD BECOES ONLY WITH THIS WAY of inheretecne SUCH THING AS CANSELING OUT SOME COMPEONTS OF SOME MOB IS POSSIBLE look LOOOK HOW IT WORKS becoes your inherated clases will call ONLY your base class consturctor implementation where you add you copmeontns THEN WHAT IT MEANS IS THAT IFF like you have like mob bowman AND i inheret from that gunman WHAT IT MEANS IS THAT I WILL BE ABLE to make sep function FOR EACH MOB BASICLY where i add UNIQUE COMPOENTS TO EACH MOB which will not go down to inheratence BEOES it will add thoes compoentns ONLY IFF I MAKE THAT CLASS as ocncreat class cos it will call sepial funciton which basicly add bow compoents for bow man BUT when gun man inehret form bow man IT WILL NOT HAVE a bow cos he just  NOT CALL THAT VERSION OF THAT FUCNTION isnetd he will call its version of that fucniton and add gun
	//4.1.3.1 AGAIN what you will do in code is MAKE IN MOB some funciton call it UniqueCompoents so you make it or virtual or just overload(VIRTUAL IS BETTER DO IT PORBABLY) it i dont' knwo BUT BASICLY the idea is that I WILL IMPLEMENT NEW VERTION OF THIS FUNCTION FOR EACH AND EVERY MOB  AND THIS FUNCTION WILL JSUT ADD UNIQUE COMPEONTS WHICH IWLL HAVE ONLY THAT MOB CONCRETA VERSION OF THTA MOB NOT SOMEHOW THROUGH BASE CLASSES I CALL IT AND ADD THOES COPMEONTS so only concreat classes will call only ITS Unique implementation and will add only to itself thoes unique compeotnns like i said bowman call it and add for himself a bow but inhereted mob gunman (whihc inehereted fomr bow man) will call this function and get a gun for himself
	//4.1.3.2 I WILL NEED TWO HTINSG FIRTS thta this fucniton whodu lcall automaticly NO MATTER WHAT without my munyal calling AND SECOND is that i whoudl MUST OVERRIDE THIS FUCNTION SO MAKE IT PURE VIRTUAL COS I ANNOT CALL THE IMPELMENTATION OF SOME PREVIOSU BASE CLASS(or somhwo make mob impelmentation which is empty BUT  PROBABLY IF I HAVE HIGER IMPLEMENTATION I WILL STILL INHERENT FOMR IER ONCE and call not my version of the fucniton SO MAKE IT PURE VIRTUAL
	//4.1.3.3 ALSO OFCORES i will make SOME of the implememntations JUST EMPTY COS FOR SOME MOBS I DO NOT WANAN ANY UNIQUE COMPEONTNS!!!!!

}

void OOMob::AddComponentToMob(MobComponentTypes MobComponentType)
{
	Components.emplace_back(OOMob::TheMobManager->AddComponentToArrayOfComps(MobComponentType)); // by this i have to add compoent to mov basicly that compoent whodul be conected to  mob by ID of mov!!
}

const std::vector<OOMobComponent*>& OOMob::GetAllComponents() const
{
	return Components;
}

void OOMob::InitTheMobManager(OOMobManager* TheMobManager)
{
	OOMob::TheMobManager = TheMobManager;
}

//template <class ComponentType>
//ComponentType* OOMob::GetComponent() const
//{
//	auto FoundComponent = Components.find(ComponentType::ID);
//	if (FoundComponent != Components.end() )
//	{
//		return FoundComponent.second;
//	}
//	 else
//	{
//		return nullptr;	
//	}
//}


OOMobManager* OOMob::TheMobManager = nullptr; // OOMob::TheMobManager1;//&OOMobManager(); delete it usless