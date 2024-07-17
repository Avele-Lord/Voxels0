#include "RenderableComponent.h"


// somwhere at the top we shoudl have memory pool defenition

RenderableComponent::RenderableComponent()
	:
	Texture(nullptr)
{}

RenderableComponent::~RenderableComponent()
{
	delete[] Texture;
	Texture = nullptr;
}

// THIS init basicly take data and init ALL VARIABLES of the component with thta data! 
bool RenderableComponent::Init(void * ComponentData)
{
	// TODO 
	Texture = new unsigned char[512];
	return true;
}