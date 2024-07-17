// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "MobOld.h" // need
#include "Camera.h" // need
#include <random>


MobOld::MobOld(Vec3 Position, int Health, int PositionNumInArray)
	:
	Position(Position),
	Health(Health),
	PositionNumInArray(PositionNumInArray)
{}


void MobOld::MoveTo(Vec3 TargetToMoveTo)
{
	const Vec3 PointToMoveTo = Vec3(TargetToMoveTo.X, TargetToMoveTo.Y, TargetToMoveTo.Z) - Position;

	// Dead zone radius = sqrt( 2 )
	if (PointToMoveTo.GetLengthSq() > 2.0f)
	{
		Position += PointToMoveTo.GetNormalized() * 1.0f;
	}
}


std::optional<HealthState> MobOld::TakeDamage(int Damage)
{
	Health -= Damage;
	return {};
}


void MobOld::Die()
{}



Vec3 MobOld::GetPosition() const
{
	return Position;
}
int MobOld::GetHealth() const
{
	return Health;
}
int MobOld::GetPositionNumInArray() const
{
	return PositionNumInArray;
}



void MobOld::SetPosition(Vec3 Position)
{
	this->Position = Position;
}
void MobOld::SetHealth(int Health)
{
	this->Health = Health;
}
void MobOld::SetPositionNumInArray(int PositionNumInArray)
{
	this->PositionNumInArray = PositionNumInArray;
}


const int MobOld::ZeroHelth = 0;