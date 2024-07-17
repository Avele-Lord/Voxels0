#pragma once
#include "New2023MobSystemTypes.h"


class New2023MobManager;
class New2023Mob;

class New2023BaseMobSystem
{
public:
	explicit New2023BaseMobSystem(New2023MobManager* MobManager_P_IN)
		:
		MobManager_P_M(MobManager_P_IN)
	{}
	virtual ~New2023BaseMobSystem() = default;
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
	virtual void OnMobCreated(const New2023Mob& Mob_IN) = 0; // it's needeed hwne entity created TO NITIFY to add compoentnts of new entity in systems lists of comeponttns to update
	virtual void OnMobDestroyed(MobID_TD MobID_IN) = 0;// well ofcorse we need to delet form lisst of systems compeotntns which are destorid COS ENTITY IS DESTROYID
	virtual void Update(float DeltaTime) = 0;

protected:
	New2023MobManager* MobManager_P_M;
};