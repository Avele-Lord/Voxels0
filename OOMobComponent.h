#pragma once
#include "MobSystemTypes.h"
//#include <numeric>




//////////MY ECS ////   start///////////

// 1: SO in my ECS EACH individual component(not just class but like WeaponComp MyWeapon1 , MyWeapon2 , MyWeapon3 EACH MyWeapon? WQILL HAVE UNIQUE INDEX IN IT'S ARRAY IT WILL HELD INDEX TO WHERE IT LIVE IT'S GENIOUS! AND EASY
// 2: SO in my ECS EACH individual component(not just class but like WeaponComp MyWeapon1 , MyWeapon2 , MyWeapon3 EACH MyWeapon? WQILL HAVE THE MOB ID TO WHICH IT BELONS TO!







// i should  MAY BE PROBABLY put this enum class in another file! 
// may be i won't need this enum class AND JUST COMPONENTN IDS AT ALL!!!
enum class MobComponentTypes : unsigned int // actualy hsould call it MobComponentIndexes or like may be MobComponentIDs
{
	TransformComponent,
	RenderableComponent,
};



class OOMobComponent
{
public:
	OOMobComponent();
	virtual ~OOMobComponent() = default;
	virtual bool Init(void* ComponentData) = 0;// TODO  // so it somhow just load data by asignig each data thing from data you passed to component variables   // it probably won't have as parameter void* more like some data class or whatever for passing data
	void SetMobId(MobIdTD MobIdIn); // TODO:  make be make setters private? 
	MobIdTD GetMobId() const;
	void SetPoolIndex(size_t PoolIndexIn); // TODO:  make be make setters private?
	size_t GetPoolIndex() const;
	MobComponentTypes GetCompType() const;
	CompIndexTD GetCompIndex() const;
private:
	//insted of size_T use uint64 //static constexpr size_t INVALID_POOL_INDEX = std::numeric_limits<size_t>::max(); // find corect heador or corect name for std::numeric_limits<size_t>::max();


	//MobComponentIDTD MobComponentID;
	MobComponentTypes MobComponentType;
	MobIdTD MobId;
	CompIndexTD CompIndex;
};



//////////MY ECS ////   end///////////



//////////ORIGINAL ECS ////   start///////////


//
//
//
//// i should  MAY BE PROBABLY put this enum class in another file! 
//// may be i won't need this enum class AND JUST COMPONENTN IDS AT ALL!!!
//enum class MobComponentTypes : unsigned int // actualy hsould call it MobComponentIndexes or like may be MobComponentIDs
//{
//	TransformComponent,
//	RenderableComponent,
//};
//
//
//
//class OOMobComponent
//{
//public:
//	OOMobComponent();
//	virtual ~OOMobComponent() = default;
//	virtual bool Init(void* ComponentData) = 0;// TODO  // so it somhow just load data by asignig each data thing from data you passed to component variables   // it probably won't have as parameter void* more like some data class or whatever for passing data
//	void SetMobId(MobIdTD MobIdIn); // TODO:  make be make setters private? 
//	MobIdTD GetMobId() const;
//	void SetPoolIndex(size_t PoolIndexIn); // TODO:  make be make setters private?
//	size_t GetPoolIndex() const;
//
//private:
//	//insted of size_T use uint64 //static constexpr size_t INVALID_POOL_INDEX = std::numeric_limits<size_t>::max(); // find corect heador or corect name for std::numeric_limits<size_t>::max();
//
//	MobIdTD MobId;
//	size_t PoolIndex;
//};

//////////ORIGINAL ECS ////   end///////////
