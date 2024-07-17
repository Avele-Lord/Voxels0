#include "AllBlocks.h"


Block AllBlocks[7];


void AllBlocksInitG()
{
	// EACH of ehse block's HP ware with one more zero at the end like not 5 but 50 not 150 but 1500 etc (just need to cut em COS i make HP unsigned chare probably change it later
	AllBlocks[static_cast<int>(BlockNames::Empty)] = Block(BlockNames::Empty, static_cast<int>(BlockNames::Empty), 0, true);
	AllBlocks[static_cast<int>(BlockNames::Snow)] = Block(BlockNames::Snow, static_cast<int>(BlockNames::Snow), 1, true);
	AllBlocks[static_cast<int>(BlockNames::Stone)] = Block(BlockNames::Stone, static_cast<int>(BlockNames::Stone), 10, true);
	AllBlocks[static_cast<int>(BlockNames::HotStone)] = Block(BlockNames::HotStone, static_cast<int>(BlockNames::HotStone), 50, true);
	AllBlocks[static_cast<int>(BlockNames::EvilStone)] = Block(BlockNames::EvilStone, static_cast<int>(BlockNames::EvilStone), 150, true);
	AllBlocks[static_cast<int>(BlockNames::Grass)] = Block(BlockNames::Grass, static_cast<int>(BlockNames::Grass), 5, true);
	AllBlocks[static_cast<int>(BlockNames::Dirt)] = Block(BlockNames::Dirt, static_cast<int>(BlockNames::Dirt), 5, true);
}
