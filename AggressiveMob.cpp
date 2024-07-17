// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "AggressiveMob.h" // need


AggressiveMob::AggressiveMob(Vec3 Position, int Health, int Damage, int PositionNumInArray)
	:
	MobOld(Position, Health, PositionNumInArray),
	Damage(Damage)
{}


void AggressiveMob::Attack()
{
	GetHealth();
}


int AggressiveMob::GetDamage() const
{
	return Damage;
}


void AggressiveMob::SetDamage(int Damage)
{
	this->Damage = Damage;
}