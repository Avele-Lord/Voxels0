#pragma once
// Refactored 04.11.2021	// Looked Through 04.11.2021


enum class BlockNames // or call it block names ////////// may be make it in Block class inside or ouside in thta file?????
{
	Empty, // 0 // IT START WITH 0 BUT MY BLOCK COUNT START WITH 1 COS 0 BLOCK IS EMPTY BLOCK!!!!!
	Snow, // White // 1
	Stone, // Grey // 2
	HotStone, // Red //HotRock // 3
	EvilStone, // Purple // 4
	Grass, // Green // 5
	Dirt // Brown // 6
};



class Block
{
public:
	//Block() = default;// May use this later
	Block();
	Block(enum class BlockNames Name, int ID, int HP, bool IsInitialized);
	enum class BlockNames GetName() const;
	int GetID() const;
	int GetHP() const;
	bool GetIsInitialized() const;
private:


private:
	enum class BlockNames Name;
	int ID;
	int HP;
	bool IsInitialized;
	/// ADD THESE IN HERE i'll add LATER
	// float WalkSpeed;
	// ??? Texture
	// float PhysicalResistant
	// float MagickResistant
	// float ???Resistant (make lake don't know lazer risistance or risistance to ALL incoming damage OR SOMTHING MORE RISISTANCE like 10 different risistances on top of two standart!!!!)
	// ??? SoundWhenStepping
	// ??? SoundWhenDamagingBlock
	// ??? SoundWhenBlockDemegingWhoStepsOrStaysOnIt 
	// ??? SoundWhenDestoruid
	// ??? SoundWhenPutting
	// bool Physics; // will block have phicis of faling or droping or will it fly in the are(liek send in minecraft has some basic phicis MOST OF OTHER BLOCKS don't have phicis and iwll fly in sky )
	// int NumOfBlockPartDrop //(RIMEMBER block cannot drop more part than you need to creat one block AND usualky it will drop less part than you nee to create one block)
	/// .... THIK WHAT ESLE VARIABLE SHUOLD BE HERE  
};