#pragma once

typedef unsigned int MobID_TD;
constexpr MobID_TD InvalidMobID = 0;

// considering MobComponentID_TD is just TYPE of compoentn SO MAKE NORMLA NAME FOR IT RENAIM IT AS TYPE not ID ok
typedef unsigned int MobComponentID_TD; //(NEW ME confirmed it's compeontn type so it sorta can be enum which say it's like transfomr or rendarble and ID cos it asigns ofcorse number to its name type etc AND YES we use it to index in pool on outer axis in vectors of compeontns itself) for me it seems that it's ""PoolIndex_M"" in class New2023MobComponent I DONT KNOW WHY HE CALLD it just ID cos he said it itse'f it's index in outer axis of pool YET he put just ID insted of PoolIndex_M