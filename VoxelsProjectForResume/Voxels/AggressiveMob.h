#pragma once
// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "MobOld.h" // need


class AggressiveMob : public MobOld
{
public:
	void Attack();
	virtual ~AggressiveMob() = default;
protected:
	AggressiveMob(Vec3 Position, int Health, int Damage, int PositionNumInArray);
	AggressiveMob() = delete;
// Inheritance interface start

	int GetDamage() const;


	void SetDamage(int Damage);

// Inheritance interface end
private:
	int	Damage;
};