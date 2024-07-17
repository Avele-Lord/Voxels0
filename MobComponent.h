#pragma once
//#include "MobSystemTypes.h"
#include <numeric>


// delet this predeclaraitonline when you transver this enum class in another file
enum class MobComponentType_EC : unsigned int; // OK i'm not shue about this predeclaration it's probabbly wrong


class MobComponent
{
	// well diriveved cocnretaclassesl iek rendercompeonttn etc 
	// they MUST have data in here all there data variables 

public:
	// so ok and in concrete compeonent class like HealthComepotntn
	// you jsut asing to MobComponentType_M so asing to it or evne init with 
	// with  basicly do this MobComponentType_M = HealthComponentType_ECV
	// ritgh it's helth compeontt it must hodl it's hetl compeontnt type
	MobComponentType_EC MobComponentType_M; // may be it shoudl be private or protected

private:
	// i am not shure if Type and Id shoudl be PRIVTE?? may be they shoudl be publick
	// ok dude this variable MobComponentType_M is basicly old """ size_t PoolIndex_M; """ so it was called bool index
	// SO what pool index ment and did is IT WAS LIKE REMEMEBR THAT POOL OF COMEPONTNT VECTORS
	// SO it was indexing NOT INTO SPECIFIC VECTOR OF COMPEOTNTS TO GET COMPEONTNT
	//  no insted it was just indexing and hoosing which vector off compeonttns it is like if renderable comepotntns thne pool index whoudl reutnr you rendarable vector of compeonttns if you index into pool with it
	// BASICLY description fomr befor """"""for me it seems that it's ""PoolIndex_M"" in class New2023MobComponent I DONT KNOW WHY HE CALLD it just ID cos he said it itse'f it's index in outer axis of pool YET he put just ID insted of PoolIndex_M
	// SO I DONT EVNE KNOW DO I NEED IT IN MY VERSION OF ECS OR NOT COS I PROBABBLY WONT HAVE MEMORY POOOL
	// SO I DONT EVNE KNOW WHERE WHUOLD I USE IT
	//static constexpr MobComponentType_EC MobComponentType_M; ok init it liek in reder class like thhis //static constexpr MobComponentType_EC MobComponentType_M = MobComponentType_EC::New2023RenderComponent_EC;
	
	

};




// move it SOMWHERE OUTSIDE in other file
// EC standsrt for "enum class"  and ECV stands for "enum class VALUE"
enum class MobComponentType_EC : unsigned int
{
	TransformComponentType_ECV,
	RenderComponentType_ECV,
	HealthComponentType_ECV,

};





///// from New2023RenderComponent.h file


#pragma once
#include "New2023MobComponent.h"


class New2023RenderComponent : public New2023MobComponent
{
public:
	New2023RenderComponent()
		:
		Texture_P_M(nullptr)
	{}
	virtual ~New2023RenderComponent() override // delete data IFF data uses "new" memory alocation (well aloates memory on the heep)
	{
		delete[] Texture_P_M;
		Texture_P_M = nullptr;
	}

	virtual bool Init(void* MobComponentData) override final
	{
		Texture_P_M = new unsigned char[512];
		// do initialisation of compoentn from passed data
		return true;
	}

public:
	//static constexpr MobComponentID_TD ID; // for me it seems that it's ""PoolIndex_M"" in class New2023MobComponent I DONT KNOW WHY HE CALLD it just ID cos he said it itse'f it's index in outer axis of pool YET he put just ID insted of PoolIndex_M
	//static constexpr MobComponentType_EC MobComponentType_M = MobComponentType_EC::New2023RenderComponent_EC;


	unsigned char* Texture_P_M; // IT can be any data of compeontnt AND IT'S ALWAS PUBLICK 
	// we can add NOT ONE VARIABLE DATAT BUT SEVERAL variables here like texture and some render thing and etc or for transfomr it's rotation tranlsation etc
};



///// from New2023TransformComponent.h file


#pragma once
#include "New2023MobComponent.h"
#include "Vec3.h"




class New2023TransformComponent : public New2023MobComponent
{
public:
	New2023TransformComponent()
		:
		Rotation_M(0.0f),
		UniformScale_M(1.0f)
	{}
	//virtual ~New2023TransformComponent() override; // delete data IFF data uses "new" memory alocation (well aloates memory on the heep)

	virtual bool Init(void* MobComponentData) override final
	{
		// do initialisation of compoentn from passed data
		return true;
	}

public:
	//static constexpr MobComponentID_TD ID; //(NEW ME confirmed it's compeontn type so it sorta can be enum which say it's like transfomr or rendarble and ID cos it asigns ofcorse number to its name type etc AND YES we use it to index in pool on outer axis in vectors of compeontns itself) for me it seems that it's ""PoolIndex_M"" in class New2023MobComponent I DONT KNOW WHY HE CALLD it just ID cos he said it itse'f it's index in outer axis of pool YET he put just ID insted of PoolIndex_M
	static constexpr MobComponentType_EC MobComponentType_M = MobComponentType_EC::New2023TransformComponent_EC;
	Vec3 Position_M;
	float Rotation_M; // you can make rotation with euelor (oilor) angles OR quaterniens
	float UniformScale_M;
};