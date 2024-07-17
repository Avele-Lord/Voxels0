#pragma once
//#include "MobSystemTypes.h"
#include <vector>


class BaseMobSystem; // OR MobSystem
class MobComponent;


// remeber naming convention all (systems compoentns manager must have prfix "Mob" infront)
class MobManager
{
public:
	MobManager();
	~MobManager();
	void CreateAndInitAllMobSystems(); // well it creats and initilise all systems one by one
	void Update(float DeltaTime); //(and yeah it will call inside update funcoint ON EACH SYSTEM) ok as far as i get we will call this fucniton somwhere in our aplication(well game project itself) SO main loop of aplication WE CALL IT IN MAIN LOOP hense this funciton wont be makign like 60 times per seocnd loop insetd i will call it through main loop of my app AND this fucniton through thta will be calld 60 times per secodn




	// or easey way out isned of CreateMob fucniotn
	// i will have CREATESKELEOTN CREATEZOMBY CREATEAROW ETC
	//  basicly for eahc mob i will have its creating fucniotn 
	// which is dumb 
	// BUT AGAIN LATER I MAKE IT ALL TEMPLATED 
	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	// I FEAL LIKE CreateMob SHOUDL BE A TEMPLATED FUNCIOTN
	// COS FOR ME IT'S HARD TO IMEIGNE HOW IT' GONNA WORK WITHTOU TEMPLATES
	//////////////////////////////////////
	//////////////////////////////////////
	//////////////////////////////////////
	// OK SO MOBTYPE IS BASICLY ENUM which exist for eahc mob and it segnifyis the mob 
	// OK DUDE BASICLY ALL MOBTYPE IS JUST skeleton arrow bow zomby hero bomb bullet pistol ETC
	// SO I MEAN IT'S THOES MOB CLASSES so but NOOT CLASSES THEMSELVS OK 
	// insted it's jsut ENUM like ID so jsut INT which says ok this enum for skeleotn so hesne creta me skeleton mob
	// think may be call it MOBCLASS and not MOBTYPE 
	//Mob/*may be return MobID*/ CreateMob(MOBTYPE MOBTYPE_IN) // dont shure about what it shoudl return
	//{
		// SO HERER THE IDEA IS I SOMHOW  BASICLY ACTULY CREAT MOB WHICH I ASKED TO CREAT 
		// LIKE I ACTUALT CREAT MOB LIEK ACTUAL MOB VARIABLE INSIDE ALL MOBS VECTOR 
		// AND THNE I TAKE THAT VARIABLE I JUST CREATED AND RETURN IT SO YEAH 
		
		//AllMobs.push_back(Mob(MOBTYPE_IN));
		//return AllMobs.end();
	//}
	//////OR OR OR
	// // ok for real newer me 15.06.2023 I CAN use JUST NORMLE TEMPLATES for ceat and destory funcionts 
	// // i dont have to use variatic tmeplates JSUT USUAL TMEPALT WILL BE EAYS just templat this classo on mob thne get it from yoru vector whatever mob you need so it's easy 
	// // just figru eout how to make thse with usual templates
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// // BTW THNEY OU CAN ALSO MAKE VECTORS OF ALL MOB POTINTERS AND ALL MOB SYSTEMS ok isnetd of having for eahc mob seporet vector
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// SKELETON CTREATESKELETON();
	// ZOMBY CREATEZOMBY();
	// SWORD CREATSWORD();
	// BASICLY MAKE FOR EACH SEP THING CREATER FUNCIOTN 
	// AND HERE HWO SUCH CREATE FUNCIOTN LOOK LIKE
	// ARROW CREATEARROW()
	//{
	//	// ALLARROWS IS JUST VECTOR OF ALL MOBS ARROWS JSUT  std::vector<ARROW> ALLARROWS;
	//	//ALLARROWS.PUSHBACK(ARROW());
	//}

	// ok destory mob 
	// 	void DestroyMob(MOBTYPE MOBTYPE_IN, MOBID MOBID_IN) // MOB_ID is actualy ID of actual variable which was in the scene like not sceleton class btu that ONE PARTICULA SKELETON which playir killed or etc
	//{
		//so main idea is OFCORSE SOMHOW DESTORY the mob ok delete it from vector of all mobs this is my aim

		//size_t INDEXOFMOBIAMDESTORYING = AllMobs.find(MOBID_IN);
		// AllMobs.delete(INDEXOFMOBIAMDESTORYING);
	//}
	// void DESTORYSKELETON(MOBID MOBID_IN);
	// void DESTORYZOMBY(MOBID MOBID_IN);
	// void DESTORYSWORED(MOBID MOBID_IN);
	// void DESTORYARROW(MOBID MOBID_IN);

	// THESE TOW FUCNITONS COMPLITLY WRONG AND COPY PASTA REDO EM 
	//MobID_TD CreateMob(); // should take compoentns in as parameter (we give mob its components
	//void DestroyMob(MobID_TD MobID);

private:
	// idea of these "GENERAL" funciotn are in these fduncionts i will FACTOR OUT AS MUCH CODE as i possible can 
	// so cos my ECS for now COMPLITLY MANYAL i defenely dont wanan tho like 
	// if i change one thing in creta mob fucnoint i will have to go throw 100 mobs creta ufncoitns and change it eveyrhwee
	// SO ON ALL creat desotry mobs
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// ALSO all other manyal things IF I CAN FACTOR somthing generalise 
	// like in creta systems I WILL TYR AND I IWLL DO IT and factor out
	// so again idea is facto rout in seporet ufncoints the code which will be repeativly used in all yrou manyal things
	// and hense call these fucniotns in thoes manyal funcionts
	// cos in case somthing changes i can ealsy chaneg in one fucniotn and all other funcionts will be fixed
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	
	//CREATGENERALMOB();
	//DESTORYGENERALMOB(MOBID MOBID_IN);

	// also think of better name than "generl" fucnitons ok 
	// call these funcoitns MAY BE JSUT as is jsut "creatmob" that  is it
	// or think of better name

private:
	// can hash may be somhow like pointer to vectro and how to rienterpret that vector by using basicly mob id
	//it or may be make a tuple of again id to mob and potiner to vector
	// mind you potiner to vector not std::vector<> no do void* this will work but i have to be able to rienterpret void*
	// or may be i will actulay have to make my own memory pool for this
	// you can also implement thoes pool compeonttns by using rienterpret cast in place where you just need it and reinterprte jsut void* as whatever you need whatever is there
	//std::vector<std::vector<MobComponent> AllMobComponents; // it's my memory pool
	// OR
	//std::vector<RENDERCOMP> // or use good old vectors of components
	//std::vector<TRANSFORMCOMP> // or use good old vectors of components
	//std::vector<HELTHCOMP> // or use good old vectors of components
	




	// ok systems i htink tow ways to do it 
	// 1 or vector of potinters to base class 
	// 2 OR OK you can make it just each system singel variable
	// 2.1 you know iff i have em like single vairbales THNE MAY BE I DONT NEED BASE CLASS SYSTEM AT ALL
	// 2.1 i probbably actyaly need base class cos it jsut does nothing bad besides makign REALY GOOD SUPER BASE TMEPLATE with all the basics each system must have SO IT'S FINE LEAVE IT BE
	// |
	// std::vector<MobSystem*> AllMobSystems; 
	// OR
	// RENDERSYSTEM RENDERSYSTEM_M;
	// TRANSFORMSYSTEM TRANSFORMSYSTEM_M;
	// AISYSTEM AISYSTEM_M;

	// OK enetities
	// 1 yes can do hash map with entities
	// 2 how about all entities just in vector
	// 3 seporet vector for each seporet entity class??? (SEEMS MAKES EASEY TON OF STUFF (like systems soarting etc)
	// 4 ok hash map FOR EACH SEPORET ENTITY THIS SEEMS MAY BE EVEN BETTER than vector for each seporet entity
	// |
	// std::vector<SKELETON> ALLSKELETONS;
	// std::vector<ZOMBY> ALLZOMBYS;
	// std::vector<PIG> ALLPIGS;
	// std::vector<SWORDSMAN> ALLSWORDSMANS;
	// OR
	// std::vector<Mob*> AllMobs;
	// OR
	// std::unordered_map<MobID_TD, Mob> ALLMOBS; 
	// OR
	// std::unordered_map<MobID_TD, SKELERON> ALLSKELETONS;
	// std::unordered_map<MobID_TD, ZOMBY> ALLZOMBYS;
	// std::unordered_map<MobID_TD, SWORD> ALLSWORDS;
	// std::unordered_map<MobID_TD, ARROW> ALLARROWS;

};