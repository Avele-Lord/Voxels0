#include "OOMobComponent.h"



OOMobComponent::OOMobComponent()
	//:
	//MobId(INVALID_MOB_ID),
	//PoolIndex(INVALID_POOL_INDEX)
{}

void OOMobComponent::SetMobId(MobIdTD MobIdIn)
{
	MobId = MobIdIn;
}

MobIdTD OOMobComponent::GetMobId() const
{
	return MobId;
}

void OOMobComponent::SetPoolIndex(size_t PoolIndexIn)
{
	//PoolIndex = PoolIndexIn;
}

size_t OOMobComponent::GetPoolIndex() const
{
	//return PoolIndex;
	return 9484;//just to compile in debug mode SOME GARBO VALYE then delete this line
}

MobComponentTypes OOMobComponent::GetCompType() const
{
	return MobComponentType;
}

CompIndexTD OOMobComponent::GetCompIndex() const
{
	return CompIndex;
}
