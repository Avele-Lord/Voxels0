#pragma once
//#include "New2023BaseMobSystem.h" // i probabbly dont need it here the  "class New2023BaseMobSystem;" this line class prediclaration is enogh
#include "New2023MobSystemTypes.h"
#include "New2023Mob.h"
#include <vector>
#include <unordered_map>



// dude O STANDS FOR OLD so eveyrhting with prefix O cos it's my old and old old ECS versions



class New2023BaseMobSystem;
class New2023MobComponent;

class New2023MobManager
{
public:
	New2023MobManager();
	New2023MobManager(const New2023MobManager&) = delete;
	New2023MobManager& operator=(const New2023MobManager&) = delete;
	New2023MobManager(New2023MobManager&&) = delete;
	New2023MobManager& operator=(New2023MobManager&&) = delete;
	~New2023MobManager();

	bool Init(); // init function is basicly will call "CreateSystems" function and may be somthing else
	void CreateMobSystems();
	// update funciton will call all systems to update (so it will have huge update call for systems
	void Update(float DeltaTime) // ok as far as i get we will call this fucniton somwhere in our aplication(well game project itself) SO main loop of aplication WE CALL IT IN MAIN LOOP hense this funciton wont be makign like 60 times per seocnd loop insetd i will call it through main loop of my app AND this fucniton through thta will be calld 60 times per secodn
	{
		for (New2023MobSystem* MobSystem : AllMobSystems) // shoudl it be New2023BaseMobSystem or New2023MobSystem???
		{
			MobSystem->Update(DeltaTime);
		}
	}

	MobID_TD CreateMob(); // should take compoentns in as parameter (we give mob its components
	void DestroyMob(MobID_TD MobID);

private:
	using AllMobs = std::unordered_map<MobID_TD, New2023Mob>;
	using AllMobComponents = std::vector<std::vector<New2023MobComponent*>>;
	using AllMobSystems = std::vector<New2023BaseMobSystem*>;

	AllMobs AllMobs_M;
	AllMobComponents AllMobComponents_M;
	AllMobSystems AllMobSystems_M;

	//std::vector<SomeComponentClass> AllSomeComponentClassComponents; 
	
	

	//std::vector<ComponentPool> AllMobComponents_M;

	std::vector<CollisionComponent> AllCollisionComponents;
	std::vector<HPComponent> AllHPComponents;
	std::vector<MagicComponent> AllMagicComponents;
};