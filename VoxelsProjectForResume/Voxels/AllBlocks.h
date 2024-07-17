#pragma once
/// I WILL NEED TO MOVE THIS INIT FROM GLOBAL RAM JUST TO SAVED FILE SOMWHERE ON SDISK(HDD SDD) cos if i will be keeping ALL weapon damage and hp of mpbs and all items etc etc ON RAM i will porbably be like eating 100mb RAM just for nothing cos i shoudl keep it on disk cos this info never changes!
#include "Block.h"


#ifndef AllBlocksCArray
#define AllBlocksCArray
///*inline*/ /*constexpr*//*extern*/ Block AllBlocks[7];
#endif

void AllBlocksInitG(); // G stands for Global
