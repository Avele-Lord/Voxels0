#pragma once
#include "New2023BaseMobSystem.h"
#include "New2023Mob.h"
#include <vector>


template <class... Comps>
class New2023MobSystem : public New2023BaseMobSystem
{
public:
	// here i'm just showign how generaly ANY concreat derived system from this base system class will work 
	void Update(float DeltaTime, Context** Context_PP) //  Context_PP is basicly a pointer to WHOLE ARRAY of pointers TO one entity chousen indexes so indexes for chousen compoentns by this system basicly
	{
		for (Context* Context_P : Context_PP) // in this for loop we basicly take one entitie'S compoentns which needed for this system AND updating this entity and so for loop runs through all fited entties
		{
			Move(Context_P->TransformIndex->Pos);
			ValidatePos(Context_P->PhysicsComponent, Pos);
			Context_P->TransformIndex->Pos = Pos;
		}
	}
	New2023MobSystem(New2023MobManager* MobManager_P_IN)
		:
		New2023BaseMobSystem(MobManager_P_IN)
	{}
	virtual ~New2023MobSystem() = default;
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;

	virtual void OnMobCreated(const New2023Mob& Mob_IN) override final; // it's needeed hwne entity created TO NITIFY to add compoentnts of new entity in systems lists of comeponttns to update
	virtual void OnMobDestroyed(MobID_TD MobID_IN) override final;// well ofcorse we need to delet form lisst of systems compeotntns which are destorid COS ENTITY IS DESTROYID
	virtual void Update(float DeltaTime) override final;

private:
	// recursivly looks through component types
	template <size_t INDEX, class CompType, class... CompArgs>
	bool ProcessMobComponent(MobComponentID_TD MobComponentID_IN, New2023MobComponent MobComponent_P, CompTuple& TupleToFill);

	// this is th etermination specialiation of the recursion which happons when we no logner have a CompType that's passed in
	template <size_t INDEX>
	bool ProcessMobComponent(MobComponentID_TD MobComponentID_IN, New2023MobComponent MobComponent_P, CompTuple& TupleToFill);


protected:
	using CompTuple = std::tuple<std::add_pointer_t<Comps>...>; // a tuple of compoentn pointers
	std::vector<CompTuple, PooledEastlAllocator> Components_M;// it's basicly references to each component of entities ENTITIES WHICH MATCHED THE REQUIERMENTS and have all necesery required components to be updated by this system

private:
	using MobIDToIndexMap = std::unordered_map<MobID_TD, size_t, std::hash<MobID_TD>, std::equal_to<MobID_TD>, PooledEastlAllocator>;
	MobIDToIndexMap MobIDToIndexMap_M;
};


template <class... Comps>
void New2023MobSystem<Comps...>::OnMobCreated(const New2023Mob& Mob_IN)
{
	// loop through all the compoentnts on this entity and see if any tuples match
	// so hense IFF this function in base class it asign entities for EACH SYSTEM and not only for on
	CompTuple CompTuple_L;
	size_t MatchingComps = 0;
	for (auto& CompPair : Mob_IN.GetComponent())
	{
		if (ProcessMobComponent<0, Comps...>(CompPair.first, CompPair.second, CompTuple_L))
		{
			++MatchingComps;
			if (MatchingComps == sizeof...(Comps))
			{
				Components_M.emplace_back(std::move(CompTuple_L));
				MobIDToIndexMap_M.emplace(Mob_IN.GetID(), Components_M.size() - 1);
				break;
			}
		}
	}
}

template <class... Comps>
void New2023MobSystem<Comps...>::OnMobDestroyed(MobID_TD MobID_IN)
{
	const auto FindIt = MobIDToIndexMap_M.find(MobID_IN);
	if (FindIt != MobIDToIndexMap_M.end())
	{
		// move the back element to verwirte this one
		Components_M[FindIt->second] = std::move(Components_M.back());
		Components_M.pop_back();

		// We need to fugruye out which entry the moved compeontts belown to so we can update the id to idex map.
		// since all comeponts in a single tuple are ownde by the same entity we can just grab the first one and query its id.
		const auto* MovedComp_P = std::get<0>(Components_M[FindIt->second]);
	
		// find the entry for the moved id and update it with the new index
		auto MovedTupleIt = MobIDToIndexMap_M.find(MovedComp_P->GetMobID());
		//assert(MovedTupleIt != MobIDToIndexMap_M.end());  it shoudl be win10 assert funcoitn
		MovedTupleIt->second = FindIt->second;
	}
}

template <class... Comps>
template <size_t INDEX, class CompType, class... CompArgs>
bool New2023MobSystem<Comps...>::ProcessMobComponent(MobComponentID_TD MobComponentID_IN, New2023MobComponent MobComponent_P, CompTuple& TupleToFill)
{
	if (CompType::ID == MobComponentID_IN)
	{
		std::get<INDEX>(TupleToFill) = static_cast<CompType*>(MobComponent_P);
		return true;
	}
	else
	{
		return ProcessMobComponent<INDEX + 1, CompArgs...>(MobComponentID_IN, MobComponent_P, TupleToFill);
	}
}

template <class... Comps>
template <size_t INDEX>
bool New2023MobSystem<Comps...>::ProcessMobComponent(MobComponentID_TD MobComponentID_IN, New2023MobComponent MobComponent_P, CompTuple& TupleToFill)
{
	return false;
}

