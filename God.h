#pragma once
// Refactored ??.??.2021	// Looked Through 15.09.2021
//#include "MobOld.h" // Do not delete for later implementations
#include <memory> // need
#include <vector> // need
/*// JUST FOR TEST DELET IT */ #include "Vec3.h" // JUST FOR TEST DELET IT

// Move all Camera moving logic (and may be input) here
class God
{
public:
	God(/*std::vector<std::shared_ptr<MobOld>> AllMobs // Implement later*/std::shared_ptr<class std::vector<class Zombie>> Zombies, class Camera& Camera);
	void Shoot();
	/*// ONLYE FOR A TEST! */void ShootAI (/*WeaponClass Weapon,*/ Vec3 MobPos/*,std::vector<*MobOld> AllMobs*/   );//this function should take these oarams( FIRST some weapon class to get precision for eacht unique weapon SECOND the pos of the mob(AI mob probably  OR one which we control as in strategy camera but not directly) THIRED all Mobs in the game(or literaly all or only shootable once!!!) ) 



private:
	class Camera& Camera;
	//std::vector<std::shared_ptr<MobOld>> AllMobs; // Implement this system later when i have reference to All Mobs for now too complected not worth it
	std::shared_ptr<class std::vector<class Zombie>> Zombies;
	//Camera GodCamera; // Imbed Camera Object here // NOT REFEENCE
	// Implement abilities weapons guns etc etc etc etc ... 8 hours later etc etc etc etc
	int Health;
	int Damage;
};