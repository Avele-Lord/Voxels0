#pragma once
#include "MobSystemTypes.h"
#include "OOMobManager.h"
#include <unordered_map>



//////////MY ECS ////   start///////////
class OOMobComponent;
class OOMobManager;





///
///
///
///
///
// two things
// FIRST each mob which need to put like bow or some weapon or some big gun or some armor WILL(USUALY not alwas tho sotmims YEAH somtims in mob will be just build in exectly one tupe of gun and you will not be able to change on anything else) so BASICLY MOST OF THE TIMES THOS you will just have STRAIGHT UP pointer to Mob just the most basick 1th hierarcy mob class COS in this mob you cna PUT ANYTHING and whne you create laft and righ hand for liek skeleton YOU WANNA BE ABLE to put in that ANYTHING liek sword bow sheald pease of mattle spider nothing ETC ETC ETC BASICLY PUT THERE anything i want AND IIF i make liek weapon for his hand then he will be bale to whold only wepaon SO COS OF THAT each hand for skeleton will be just Mob* and alredy  later i can asign to thoesm osb to be Bow or Swors etc
// SECOND agsign mobs and transfer asigment through ALL hierarcy basicly what i mean best is IFF like on 3th level of hierarcy i asign EXECTLY TO THAT MOB like EXECTLY big sword I WANNA ALL MOBS inhereted form that mob have asign big sword in the same hamd slots(well Mob* ) and asign EXECTLY same big sword so so 4th etc hierarcy whoudl be automaticly asign thta sword
// SECOND.1 ACTUALY it's or bad exmaple or may be i want somthing lie this read COS iff i asign big sword in 3th hierarcy i wanna asign MAY BE some other hting for 4th hierarcy BUT GENERALY if i find better example thne yeah NOT ALWS OFCORES BUT OSMTIMS i wanna transfer my previous hierarcy asigments BUT AS IT TURNS OUT 90% OF THE TIME I WANNA REWRITE ON SOME NEW ASIGMENT!!!
///
///
///
///
///
///
///








//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!
///1  so ALL mobs whcih are not contreat but just made for inheretiong other mobs will have """ Mob""" word at the end LIKE not Weapon but WeaponMob
/// 2 ALSO I WILL MUST MAKE BASE CLASSES FOR EVERYTHING EACH MOB IN THE GAME WILL INHERET AT LEAST FROM SOME BASE CLASS AND NOT FROM MOB DIRECTLY
///2.1 AND EVEN MORE MOBS INHERET from one base class BUT that base class inhereted not just form mobw but form other base class BASICLY 
///2.1.1 basicly hierarcy of base AND NOT concrt pure virtual objstract classes won't be just mob and liek Weapon mob cos look mob is 1th level in hierarcy weaponMob is 2th levol in hierarcy WHAT I WANNA is like 5th or even 10th level of hierarcy for some mobs less for some mor OF JUST PURE VIRTUAL BASE CLASSES
///2.1.2 like look i wanna have like ok Mob 1th THE main of all 2th is CreatherMob which basicly anything living or not living liek unded or skeleton or zomby or player etc so form that i can make 3th well i don't know agresivecrether WELL BAD IDEA that alredy was a htink and it was dumb well LETS DO IT SIMPELER PersenMob BUT yeah porbably just Persen cos i will be able to spawn JUST Persen but whatever the 4th will be PersenWarier and 5th will be Sniper or whatever but you get it
///2.1.2.1 BAD EXAMPLE for real it porbably as i see it will be mainly only to 2th abstract classes AND THEN like i make CreatherMob and form that i start inehereting ALL UNITS and skeletons and player etc 
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
///2.1.3 BUT OFCORES if we tlakign not about jsut abstract classes THNE I CAN SAY THTA I IWLL HAVE LIEK 20TH and 100th and 1000th hierarcy LIKE LOOK AT THIS ONE very easy LIKE in civilization 6  just do catapult thne ineheret form that trebushe thne form that bigGun then form thta Artilery then fomr that RocetArtilery YEAH IT'S THTA COOL!  
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!


// 1: SO multiple components of the same type on one entity(i.e 3 weapon components on one entyity ) 
// 1.1: todo so i will be just making just like WeaponComponent MyWeapon1; WeaponComponent MyWeapon2; WeaponComponent MyWeapon3;
// 1.1: so just vatiable NO vectors of the same component just seporet variabnles of the same component
// 2 AGAIN dont' forget it's MYECS SO i won't have get compoentn function INSTED i will have just each variable NOT PRIVATE byt publick exposed
// 2.1 ALSO i will have all functions names (basicly take em form system) to see what this mob actualy can do or what i can do with it 
// 2.2 AGAIN it's all just for easer understanding 


class OOMob
{
public:
	explicit OOMob(MobIdTD MobId);
	~OOMob() = default;
	OOMob(const OOMob&) = delete;
	OOMob& operator=(const OOMob&) = delete;
	OOMob(OOMob&&) = default;
	OOMob& operator=(OOMob&&) = default;
	//MobIdTD AddThisMobToTheMobManager();  // Adding mob into mob manager vector of all mob pointers
	//MobIdTD CalculateNewIDForMob();
	void AddUniqueMobComponents(); // i will overload this function FOR EACH mob and will be calling AUTOMATICLY but only on concreat mob classes on inhereted hiearcy mobs in bitwen which rae base classes for inhereetd classes i wont' call this funciton 
	void AddComponentToMob(MobComponentTypes MobComponentType);
	//void AddComponent(ComponentId ComponentIdIn, OOMobComponent* MobComponentIn);
	//MobIdTD GetId() const;
	const std::vector<OOMobComponent*>& GetAllComponents() const;
	/// this funciton not gonna work for me cos i'm gonna have on one entity MORE THAN ONE component of the same type like i can have ntity with for hands and hense 4 wepons component AND this function works IFF each entity has only one component of some type like onlye one weapon and not more! 
	//template <class ComponentType>
	//ComponentType* GetComponent() const;
	static void InitTheMobManager(OOMobManager* TheMobManager);



protected:
	std::vector<OOMobComponent*> Components; // DUDE IT WAS AN IT MUST BE IN PRIVATE SECTION(i just make it protected for tesing sorta!) in MYECS probably 
	static OOMobManager* TheMobManager;

private:
	MobIdTD ID;
};



//////////MY ECS ////   end///////////



//////////ORIGINAL ECS ////   start///////////


//
//
//
//class OOMob
//{
//public:
//	//explicit OOMob(MobIdTD MobId);
//	~OOMob() = default;
//	OOMob(const OOMob&) = delete;
//	OOMob& operator=(const OOMob&) = delete;
//	OOMob(OOMob&&) = default;
//	OOMob& operator=(OOMob&&) = default;
//	//void AddComponent(ComponentId ComponentIdIn, OOMobComponent* MobComponentIn);
//	//MobIdTD GetId() const;
//	//const ComponentMap& GetAllComponents() const;
//	/// this funciton not gonna work for me cos i'm gonna have on one entity MORE THAN ONE component of the same type like i can have ntity with for hands and hense 4 wepons component AND this function works IFF each entity has only one component of some type like onlye one weapon and not more! 
//	//template <class ComponentType>
//	//ComponentType* GetComponent() const;
//
//
//
//private:
//	//using ComponentMap = std::unordered_map<ComponentId, OOMobComponent*, std::hash<ComponentId>, std::equal_to<ComponentId>, PooledStdAllocator>; // std::equal_to<ComponentId> i am not shire about this cos it shoudl be eastl::equal_to<ComponentId>  SO find exect copy in std library of that eastl thing! // the same i'm not shure about std::hash<ComponentId> cos it hsoudl be eastl::hash<ComponentId>
//
//	MobIdTD ID;
//	//ComponentMap Components; // ORRR USE THIS COS IT'S ORIGINAL ONE //std::unordered_map<MobComponentId, OOMobComponent*> Components; // check is it corect hash map??? 
//};



//////////ORIGINAL ECS ////   end///////////

