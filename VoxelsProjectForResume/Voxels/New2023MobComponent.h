#pragma once
#include "New2023MobSystemTypes.h"
#include <numeric>

class New2023MobComponent
{
public:
	New2023MobComponent() 
		:
		MobOwnerID_M(InvalidMobID),
		PoolIndex_M(InvalidPoolIndex)
	{}
	virtual ~New2023MobComponent() = default;
	virtual bool Init(void* MobComponentData) = 0; // void* should be some other thing MORE CONCREAT THING so void* there for unknown class stands basicly

	void SetMobID(MobID_TD MobID_IN) { MobOwnerID_M = MobID_IN; } // TODO: may be do it private?
	MobID_TD GetMobID() const { return MobOwnerID_M; }

	void SetPoolIndex(size_t PoolIndex_IN) { PoolIndex_M = PoolIndex_IN; }
	size_t GetPoolIndex() const { return PoolIndex_M; }

private:
	// TODO: Consider just using uint64 insted of size_t cos it can be inconsistent and buggy bitwin 64 and 32 bit BUT if you use only 64 bit then it's fine
	static constexpr size_t InvalidPoolIndex = std::numeric_limits<size_t>::max();

	MobID_TD MobOwnerID_M;
	size_t PoolIndex_M;
}; 