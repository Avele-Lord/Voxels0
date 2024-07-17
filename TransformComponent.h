#pragma once
#include "Vec3.h"
#include "OOMobComponent.h"


class TransformComponent : public OOMobComponent
{
public:
	TransformComponent();
	//virtual ~TransformComponent() override; // TODO: this sdhould free ALL the data from member objects of the componentn! 
	virtual bool Init(void* ComponentData) override final;


public:
	static constexpr ComponentIdTD ID = static_cast<unsigned int>(MobComponentTypes::TransformComponent);
	// i probably should make it as one 3x3(OR PROBABLY 4X4 ACTUALY cos to put translation(well here it called position) into 3D world matrix i need 4x4 matrix) matrix that what(that is how Transform usualy implementid(in UE4 and Unity it's how it's implementid under the hood!) 
	Vec3 Position;
	float UniformRotation; // ROTAITON IS IN RADIANS 100%!!!!!!! // it should be Vec3 too like in UE4 and Unity
	float UniformScaling; // it should be Vec3 too like in UE4 and Unity
	// somwhere at the bottom we shoudl have memory pool declaration
};