#pragma once
#include "Mob.h"


class Skeleton : public Mob
{
	Skeleton()
	{
		Init();
	}

	// this exmapel for mob liek skeleton concreat mob TRANSLATE IT LATER to skeleotn class
	void Init()
	{
		// OK my question SHOULD IT BE MOBMAGASNER fucniotn to add compeotntns to mob
		// OR it should be MOB class funciotn which adds comepotntns to entity
		// THINK ABOUT IT 
		// COS It realy loosk acuord and wierd passing to mob manager the "this*" poitner it's liek JEE DUDE realy 

		//ALLMOBCOMPOENTNS.PUSHBACK(MOBMANAGER.ADDCOMPEONTNTTOMOB(this*, HELTHCOPMTONT));
		//ALLMOBCOMPOENTNS.PUSHBACK(MOBMANAGER.ADDCOMPEONTNTTOMOB(this*, RENDARABLECOMPTONT));
		//ALLMOBCOMPOENTNS.PUSHBACK(MOBMANAGER.ADDCOMPEONTNTTOMOB(this*, TRANSFFORMCOMPEONTTN));
		//ALLMOBCOMPOENTNS.PUSHBACK(MOBMANAGER.ADDCOMPEONTNTTOMOB(this*, SOUNDCIMCPOEONT));
		//ALLMOBCOMPOENTNS.PUSHBACK(MOBMANAGER.ADDCOMPEONTNTTOMOB(this*, AICOMPONENTS));

		//MOBMANAGER.ALLSKELETONS.PUSHBACK(this); // i can do it push it here and thne jsut create m,obs as is OR make sep create funciotn
	}

};