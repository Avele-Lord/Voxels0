#pragma once
//#include "MobSystemTypes.h"

// OK NEW IDEA IS
// i can INSTED of having mobID varibale which is basilcy INDEX in ALL vectors of copmeotntns
// but firtsi  must hash that mobID varibale so it whoudl become index which is slow
//INSTED WHAT I CAN HAVE AND DO IS for each compeontnt my mob my enitty has 
// insetd of haivng one uniform ID and thne hashign it to get index
// INSTED I JUST SOTRE LIEK  10 20 100 whatever numebr of INDEXES direclty into arrays ok 
// OK  basicly each mob will hodl dipending on what compeont it has 
// just index  into array of comeponttns the one comeponttn it has in that array
// so hense no hashign etc
// may be it wont be jsut index but insted it iwll be like pair so liek you will have comepontt type and index in one pair
// so yeah  this is th eidea
// I TOOK THIS IDEA FORM OLD note htis one @412 exectl entry 1.1*** read it all carefuly!

class MobComponent;


class Mob
{
public:
	Mob();

	void ADDCOMPOENTNT(); // this funciotn is ONLY FOR ADDING COMEPONTNTS on the fly in game to alredy existing mob NOT TO ACTUAL mob class  but jsut to speciifc mob and like be able to extend curent mob make it better and stronger and creta lkiek temorery unconcreta mob class(not realy class but jsut mob it wont be deifdned in code)

public: // or may be it shoudl be protected  I DONT KNOW 
	//hash_map<MOBID, MOBCOMPOENTN*> ALLMOBCOMPOENTNS;
	//OR
	//std::vector<MOBCOMPOENTN*> ALLMOBCOMPOENTNS;
	// MOBID MOBDID_M; 
};