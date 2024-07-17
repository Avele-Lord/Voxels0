// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "Zombie.h" // need


// Factor out this class and Mob class into some garbo collecting data holding class or at least make it ALL in Mob Class
Zombie::Zombie(Graphics& Graphics, Vec3 Position)
	:
	AggressiveMob(Position, 100, 10, Positions.size()) // Positions.size() Works only cos it's static IF NOT well, bad times
{
	Positions.emplace_back(BDS::Instance{ DirectX::XMFLOAT3(Position.X, Position.Y, Position.Z) });
	if (!Zombies)
	{
		Zombies = std::make_unique<Voxel>(Graphics, 0.0f, 0.0f, 0.0f, 1, Positions);
	}
}


void Zombie::Initialize(std::shared_ptr<std::vector<Zombie>> ZombiesPIn)
{
	ZombiesP = ZombiesPIn;
}


void Zombie::Draw(Graphics& Graphics) 
{
	Zombies->RebindInstancedBuffer(Graphics, Positions);
	Zombies->Draw(Graphics);
}


void Zombie::MoveTo(Vec3 TargetToMoveTo)
{
	MobOld::MoveTo(TargetToMoveTo);
	Vec3 PositionLocal = GetPosition();
	Positions[GetPositionNumInArray()] = BDS::Instance{ DirectX::XMFLOAT3(PositionLocal.X, PositionLocal.Y, PositionLocal.Z) };
}


std::optional<HealthState> Zombie::TakeDamage(int Damage)
{
	MobOld::TakeDamage(Damage);
	if (GetHealth() <= ZeroHelth)
	{
		Die();
		return HealthState::Dead;
	}
	return HealthState::Alive;
}


void Zombie::Die()
{
	MobOld::Die();
	int PositionNumInArray = GetPositionNumInArray();
	Positions[PositionNumInArray] = Positions.back();
	Positions.pop_back();
	ZombiesP->operator[](PositionNumInArray) = ZombiesP->back();
	ZombiesP->operator[](PositionNumInArray).SetPositionNumInArray(PositionNumInArray);
	ZombiesP->pop_back();
}


std::unique_ptr<Voxel> Zombie::Zombies;
std::shared_ptr<std::vector<Zombie>> Zombie::ZombiesP;
std::vector<BDS::Instance> Zombie::Positions;
bool Zombie::IsInitialize = false;