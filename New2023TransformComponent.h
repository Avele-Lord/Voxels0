#pragma once
#include "New2023MobComponent.h"
#include "Vec3.h"

// move it SOMWHERE OUTSIDE in other file
enum class MobComponentType_EC : unsigned int
{
	New2023TransformComponent_EC,
	New2023RenderComponent_EC,
};


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