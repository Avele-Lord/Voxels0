#pragma once
#include "MobSystem.h"

// IS_ means "incorect speling"
class RenderSystem : public MobSystem
{
	// ok these thingSSSS I MUST HAVE IN "MobSystem" in base thing some WELL JSUT SOME EMPTY REWIRTABLE FUNCITON SIGNATURES which i overwriet or not overwirte but ovelroad 
	//std::vector<RequiredCompeonttn1> again so i will have YES each compeontnt which suted in vector all reuiqred copmeonttns for system
	//std::vector<RequiredCompeonttn2> 
	// NOW OPTIONAL compeonttns THE ONLY wya they work is ONLY IFF the sparced arrays
	// WHAT i mean by that in these vectors i have FOR EACH REUIRRED PASSED MOB optional compeontnts memory present
	// BUT just memoery iwll be some null putor some will be actual optinal copmeonttn 
	// BECOES there is no other way realy cos they are optinal andi  laod entity by enitty with same reuiqred compeotnts
	// if liek i skipp some optionals i iwll lbe updating reuired copmeonttns for enitty liek 28 but optinal iwll be enitty 14 21 and 3 ok
	// so thye must be sparec
	//std::vector<OptionalCompeontn1> 
	//std::vector<OptionalCompeontn2>

	// vodi IS_CheckAllInitialENITYITYCLASSES()
	//{
	// so all this funcoint does is
	// OR AT COMPILE TIME OR AT THE VERY START OF THE GAME
	// IT WILL SCAN ALL THE MOB CLASSES OK ALL MOSB ALL SKELEOTN CLASS ZOMBY CLASS ETC
	// AND CHECK ARE THE PASSING REUQIRED COMPEONTTS
	// IF THEY DO
	// I MARK THIS CLASS AS PASSED
	// AND ALSO I WILL MARK OPTIONAL COMPEONTNTS SEPORET LIKE FOR EACH OPTINAL COMPEONTNTS
	// FOR EAHC OPTINAL OCMPEONTS I WILL HAVE A MARK LIKE THIS CALLS CONTIANS THIS OPTINAL
	// 
	//}

	// void IS_onmobcreated()
	//{
	// each time mob created
	// it will check is this mob MARKED as passed reqiermens mob
	// and if it passed it will ADD ALL IT'S REUIRED COPMEONTNTS
	// INTO systems vectors for passed copmeotntns
	// and also thne it's checks of reahc optinal copmeotntns is mob passed optinal copmeontnt or not
	// abd tgbe also add to vector 
	//}

	// void IS_onmobDESOTRY()
	//{
	// ok here i basicly  i dot knwo may be i have freelist ionthese composntnts vectors
	//  which passed and liek delet coempotntns of dleetd mob
	// but dont delet ofcorse memeory fomr vector
	// and mark that meomory in frealist as free to use for next mob
	// OR MAY BE I GO SPARS andf just delet mob compeontnts memory stays
	// but then i just keep some nuemrb of free memory
	// so whne it's way too much free memory i whoudl dleeted vcctor and recreated with no sparsnes
	//}


	// void IS_Update()
	//{
	// ofcrose i jsut go throw all my vectors of passed and optinal copmeotntns
	// and update all of em
	// BUT OPTINLAS I MUST PTU EAHC OPTINAL in if statment FIRST
	// becoes optinal may be nullputor thne we dont update it or may be normle and fine thne we do it
	//}

};