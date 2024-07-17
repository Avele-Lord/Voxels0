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