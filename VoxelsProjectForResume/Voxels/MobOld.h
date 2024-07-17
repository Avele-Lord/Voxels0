#pragma once
// Refactored ??.??.2021	// Looked Through 15.09.2021
#include "Vec3.h" // need
#include "Voxel.h" // need
#include <optional> // need


enum class HealthState
{
	Dead,
	Alive
};


class MobOld
{
public:
	virtual void MoveTo(Vec3 TargetToMoveTo);
	virtual std::optional<HealthState> TakeDamage(int Damage);
	Vec3 GetPosition() const;
	virtual ~MobOld() = default;
protected:
	MobOld(Vec3 Position, int Health, int PositionNumInArray);
	MobOld() = delete;
	virtual void Die();

// Inheritance interface start
	int GetHealth() const;
	int GetPositionNumInArray() const;


	void SetPosition(Vec3 Position);
	void SetHealth(int Health);
	void SetPositionNumInArray(int PositionNumInArray);

// Inheritance interface end
protected:
	static const int ZeroHelth;



private:
	Vec3 Position;
	int Health;
	int PositionNumInArray;
};