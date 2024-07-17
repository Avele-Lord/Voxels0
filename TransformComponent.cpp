#include "TransformComponent.h"


// somwhere at the top we shoudl have memory pool defenition

TransformComponent::TransformComponent()
	:
	Position(0.0f, 0.0f, 0.0f),
	UniformRotation(0.0f),
	UniformScaling(1.0f)
{}

// THIS init basicly take data and init ALL VARIABLES of the component with thta data! 
bool TransformComponent::Init(void * ComponentData)
{
	// TODO 
	return true;
}