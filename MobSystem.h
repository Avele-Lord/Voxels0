#pragma once


// also i've a question like with the idea of like if we do somthing somtims w ehave to notify we done that 
// and it has to react and do somthing esle 
// or liek if some data changes some system must tirger and do somthing
// like if we move we m ust thne tricer colision system to check is there colision
// SO HERE IS THE QUESTION how do i for exampel triger even that colision system on move
// LIKE IS IT FINE JUST TO call colision system from move system
// OR MAY BE IT WILL BE MROE LOGICLY like probabbly YEAH all systems update eveyr frame rigth in huge update
// SO YEAH OK colision will just be updated after move happon it check like is it even valid to move there 
// so move udpate pos colision look at new pos check coliison if no colision fine if colision move will be rjected

class MobSystem
{
public:
	void Update(); // the question what are inptu parameters I AM NOT SHURED nad it porbabbly should retunr void BUT AGAIN not shure
	// so I WIL L have some init or may be jsut system constructr
	// so and eahc system what it will do is
	// take MobManager_P_M and check EACH EXISTING MOB is it fiting required compotnts
	// and what optoinal components each mob have if it fir reuired
	// SO AND WHAT I IWLL DO INSTED OF COLECTING and having vectors of mobs andf copmeontyns in eahc system it's wastful
	// NO INSTED I IWLL HAVE JUST IN MOB MANAGER JSUT each mob is colected in it's OWN VECTOR OK 
	// and so if i check trhis mob is fited in syste,m it passe reuired
	// I JUST MARK IT AS PASSED
	// SOMHWO MARKED OPTIONAL OCPMEONTNS WHICH PRESNET FO RTHTA MOB
	// AND JSUT ON UPDATE SYA OK GRAB that vector of that particular mob IN MOB MANAGER
	// ANDI JUST ITERATE THROW ALL THAT WHOLE VECTOR 
	// and so i iterate threow	EAHC VECTOR OF MOBS whci fited requirments and that is it update em
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// now now HERE IS HUUUGE PROBLEM
	// THINK ABOUT IT IT MAY BE COPMTLITLY NOT CASH ALIGNED IF I DO THIS
	// COS THE IDEA IS i crank throw liek all algiend comepotntns in vecotr which all go one after another
	// the porblem they go in osme parrticualr order
	// and IFF i just isnetd of that order of vectors WHAT ORDE ROCMPEONTTNS HAVE IN THAT VECTOR
	// ISNETD IF MOBS in mob manager iwll be like firts go 5th comepotnts thne 150 then 3220 coempotnt etc
	// i jsut get all cash misses
	// basilcy this idea
	// you must ALWAS CHECK osmhwo make 100 % shure THAT YOUR CRNANAKING THROW EAHC SYSTEM load all copmeronttns very concecytivly AND NO CAHS MISSES CASH PREFECTER LOADS ALL AND WE CRNKA THROW ALL
	//	BECOES IT'S VEYR EASY TO MESS IT UP SO EVNE THO VECTOR IWLL BE CONCECUTIVELY AND CASH PREFECHE RLOAD THIS
	//	BUT IT CAN BE SO SYSTEM IWLL UPDATE FIRTSL IKE 15TH COMPEONTTNS IN VECTOR THEN WANT TO UPADET 21023 COMPEONTNT IN VECOTR
	//	LIEK IF IT JUMPS THOUSENDS BACK AND FORHT BITIWN COMPEORNTTNS EAHC ITME
	//	YOU WILL SITLL HAVE OTN OF CAHS MISSES COS EACH TIME INSTED OF GO OCPMEONTNTS 1 2 3 4 5 6 7 ALL COCECTYIVLY ASKIGN FOR UDPATE 1 2 3 4 5 6 7 AS IT ALIGNE IN VECOTR ITSELF
	//	YOU CAN DO LIKE 5 2100   1322   5434 165 ETC SUPER CASH MISSES
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

private:
	//MobManager* MobManager_P_M;

	// NOW I MUST DO IT THIS WUA IT'S LATEST WAY 13.06.2023
	// BECOES OTHERWISE DUDE if you have another way YOU GET CASH MISSES
	// BECOES like i iwll tyr to update like mobs which was added firts 
	// then jump to udpaitng mdidle mosb
	// then end 
	// thne midle again
	// thne end
	// thne first
	// etc IT'S MESS BECOES  COMEPOTNTNS WILL BE ALSO HENSE TH EONCE HWIHC WAS LIEK IN 100 OTHER IN 500 OTHER 3000 ETC
	// SO you jsut try to look at 100 copmeonttns thne 3000 copmeonttns it cash miss 
	// we msut go 1 2 3 4 5 6 7 etc concectuvily with cpomotntn then no cash missses we laod em all and go
	// here tho we load once htne unload lode toehrs thne laod same but we alreyd unloded em from cash
	// 1
	// ok new idea i iwll have this again 
	// std::vector<Mob*> PASSEDMOBS;
	// or may be isnetd i iwll have vectors of passed copmonets
	// 2
	// now how they pass is FIRTS i will have funcition hwihc at compoile time OR AT THE VEYR BEGINGI OF TH ESTART of loaidng of project 
	// so funciont which basiicly somhwo look at LIKE EAHC MOB CLASS ITSELF liek the compeonttns it consist of 
	// SO I WONT LOOK at each mob varibale like concreate created mob
	// INSTED I JUST LOOK at just at th ebeingign at eahc closs
	// and this ufnciotn will determin i smob passes the requirment so rnot
	// also it iwll determin is there optional compeontnts or not
	// and yeah it makesj ust osme enum list of nto enum but jsut small aray of jsut liek 50 or whatever mosb which match it
	// 3 
	// NOW at runtime what will happo nis i have another tow funcoints 
	// ONMOBCREATED and ONMOBDESTORID
	// so these two funcoitns do one thing
	// it just when new mo bis created it loosk what this mob is it skeleton or zomby or etc
	// AND it just comperes or like looks for do we have skeleton or zomby AS passed the reuirment mobs
	// and if it passe dit iwll add it in this vector of passed mobs
	// 3.1
	// for speeds up of fucnoitn ONMOBCRTEATED (may be also ONMOBDESTORID)
	// YOU CAN isnetd of some LONG FIND LOOK FO RUFNCIONT
	// just make not if else but CASE OR SWITCH YES SWITCH STATMENT
	// AND SO i inptu liek the enume for mob liek skeleton = 32 mob whatever
	// and so eahc case iwll have like skeleton zsomby etc inside em enums 
	// and SO IT WON LOOK FOR IT SUPER FASTLKY JUMP TO THERE 
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// COS DUDE these tow fucniotns iwll be caleld EAHC TIME MOB IS CREATED
	//  AND IFF you create like TON OF MOBS LIKE EACH SECON if you crteate 30k mobs each second
	// AND THIS FUNCIOTN HENSE IWLL BE CALELD EAHC TIME WHNE MOBS CREATED IF IT'S SLOW AND HAVE TO DO LONG LOOP OF LOOK FOR IT'S WILL BE VEYR BADE
	// SAME WITH ON MOB DESTORID LIEK THOES 30K MOBS PORBABBLY WIL LBE DESTORID SOON SO THAT FUCNOITN MUST BE FAST TOO
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	// 4 
	// the questio is WHAT TO DO WITH OPTIONAL COPMEONTNTS 
	// like have for em spoeret vector of optoinal copmeontns
	// or just again insed of having mobs YEAH insetd of having mobs so not vector of passed mobs
	// but vector of passed copmeonttns hense some of the vector will be vectors of optinal cpoemtnts
	// or may be somhow mark which mobs like have optinal copmeonttns and which dont have optinal copmeonttns 
	// i dont knwo think about it 


};
