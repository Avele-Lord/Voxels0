// Refactored 04.11.2021	// Looked Through 04.11.2021
#include "Block.h"


Block::Block()
	:
	Name(BlockNames::Empty),
	ID(0),
	HP(0),
	IsInitialized(false)
{}


Block::Block(BlockNames Name, int ID, int HP, bool IsInitialized)
	:
	Name(Name),
	ID(ID),
	HP(HP),
	IsInitialized(IsInitialized) // MAY BE JUST aturomaitcly make it tru COS it's anywais init constructor
{}


BlockNames Block::GetName() const
{
	return Name;
}

int Block::GetID() const
{
	return ID;
}

int Block::GetHP() const
{
	return HP;
}

bool Block::GetIsInitialized() const
{
	return IsInitialized;
}