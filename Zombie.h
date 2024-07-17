#pragma once
// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "AggressiveMob.h" // need


// Factor out this class and Mob class into some garbo collecting data holding class or at least make it ALL in Mob Class
class Zombie : public AggressiveMob
{
public:
	Zombie(Graphics& Graphics, Vec3 Position);
	Zombie() = delete;
	static void Initialize(std::shared_ptr<std::vector<Zombie>> ZombiesP);
	static void Draw(Graphics& Graphics);
	virtual void MoveTo(Vec3 TargetToMoveTo) override;
	virtual std::optional<HealthState> TakeDamage(int Damage) override;
	virtual void Die() override;
	virtual ~Zombie() = default;
	//MobOld::GetPosition; // Delete later and make public in Mob OR don't expose Pos at all

private:
	static std::unique_ptr<Voxel> Zombies;
	static std::shared_ptr<std::vector<Zombie>> ZombiesP;
	static std::vector<BDS::Instance> Positions;
	static bool IsInitialize;
};