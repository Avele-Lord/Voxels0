#pragma once
#include "OOMobComponent.h"


class RenderableComponent : public OOMobComponent
{
public:
	RenderableComponent();
	virtual ~RenderableComponent() override; // TODO: this sdhould free ALL the data from member objects of the componentn WHICH ARE WAS new (basicly if i have any pointer! )  
	virtual bool Init(void* ComponentData) override final;


public:
	static constexpr ComponentIdTD ID = static_cast<unsigned int>(MobComponentTypes::RenderableComponent);
	unsigned char* Texture;// or void*
	// it also shoudl have some variable for geometry SOMTHING LIKE BELOW
	//const std::vector<BDS::Vertex>& Vertices
	//const std::vector<unsigned short>& Indices
	//const std::vector<BDS::Color>& Colors
	//const std::vector<BDS::ColorGradient>& ColorGradients
	//std::vector<BDS::Instance> InstancesData
	// somwhere at the bottom we shoudl have memory pool declaration
};