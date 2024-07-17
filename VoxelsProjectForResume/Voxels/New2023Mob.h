#pragma once
#include "New2023MobSystemTypes.h"
#include <unordered_map>

class New2023MobComponent;

class New2023Mob
{
public:
	explicit New2023Mob(MobID_TD ID)
		:
		ID(ID) 
	{}
	//New2023Mob(const New2023Mob&) = delete;
	//New2023Mob(New2023Mob&&) = default;
	//New2023Mob(const New2023Mob&) = delete;
	//New2023Mob& operator=(const New2023Mob&) = delete;
	//New2023Mob& operator=(New2023Mob&&) = default;
	//~New2023Mob() = default;

	//void AddComponent(MobComponentID_TD MobComponentID_IN, New2023MobComponent* New2023MobComponent_P_IN)
	//{
	//	MobComponents_M.emplace(MobComponentID_IN, New2023MobComponent_P_IN);
	//}

	MobID_TD GetID() const
	{
		return ID;
	}
	//const ComponentMap& GetComponents() const
	//{
	//	return MobComponents_M;
	//}

	//template <class CompType>
	//CompType* GetMobComponent() const
	//{
	//	auto FindIt = MobComponents.find(CompType::ID);
	//	if (FindIt != MobComponents.end())
	//	{
	//		return FindIt->second;
	//	}
	//	return nullptr;
	//}

private:
	//using ComponentMap = std::unordered_map<MobComponentID_TD, New2023MobComponent*, std::hash<MobComponentID_TD>, std::equal_to<MobComponentID_TD>, PooledEastlAllocator>;    

	//unsigned long long ID; // or i should call it idex and not ID ???
	MobID_TD ID;
	//ComponentMap MobComponents_M;
	//std::unordered_map<MobComponentID_TD, New2023MobComponent*> MobComponents_M;   
};