// Refactored ??.??.2021	// Looked Through 15.09.2021
#include <vector> // need
#include <memory> // need
#include "God.h" // need
#include "RayCast.h" // need
#include "Camera.h" // need
#include "Zombie.h" // need
#include "Math.h" // ONLY NEEDED FOR GETTING PI  (so probably i need it here!!)
#include <random>// ONLY FOR TEST DELET THIS LATER!!!


// Move all Camera moving logic (and may be input) here
God::God(/*std::vector<std::shared_ptr<MobOld>> AllMobs // Implement later*/std::shared_ptr<std::vector<Zombie>> Zombies, class Camera& Camera)
	:
	Camera(Camera),
	Zombies(Zombies),
	Health(1000),
	Damage(/*35*/100)
{}


void God::Shoot()
{
	DirectX::XMFLOAT3 CamPos = Camera.GetCamPos();
	Vec3 EndLocation(CamPos.x, CamPos.y, CamPos.z);
	Rotation CamRotation(Camera.GetCamRotation());
	for (int i = 0; i < Zombies->size(); i++)
	{
		Vec3 MobPosition = Zombies->operator[](i).GetPosition();
		RayCast Ray = RayCast(EndLocation, CamRotation.Pitch, CamRotation.Yaw);  // You need initialize RayCast here cos if do only once befor the loop the variables values will stock up
		for (float Step = 0.0f; Step < 25; Step += 0.1f)
		{
			auto[EndLocation, EndLocationCorrected] = Ray.ShootARayCast();
			/// if (std::floor(MobPos.Y) == std::round(EndLocation.X) && std::floor(MobPos.X) == std::round(EndLocation.Y) && std::floor(MobPos.Z) == std::round(EndLocation.Z))
			if (MobPosition.X + 0.5f >= EndLocation.X && MobPosition.X - 0.5f <= EndLocation.X &&
				MobPosition.Y + 0.5f >= EndLocation.Y && MobPosition.Y - 0.5f <= EndLocation.Y &&
				MobPosition.Z + 0.5f >= EndLocation.Z && MobPosition.Z - 0.5f <= EndLocation.Z)
			{
				HealthState::Alive == Zombies->operator[](i).TakeDamage(Damage);
				return;
			}
		}
	}
}













///(START) ALL THIS SHOULD BE ONLY IN AI FOR MOBS AND NOT IN GOD(player) SO CUT IT LATER I JUST DO IT FOR THE TEST HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// IMPLEMENT NORMAL REANDOM CIRCULE OF PRECISION LIEK IN WORLD OF TANKS BY READING THIS(btw i alredy make card off of this) 1.3***(make fomr htis question)( and make num of steps) you can impelement some random number generator WHICH rabdomly choosis one of liek 5 or 10 or 100 or whatever things AND EACH THING has fixed chanse on choosing like things number 1 has 10% to be chosen thing number 2 has 3% and number 3 has 5% etcWE IMPLEMENT IT BY making random numebr generator which goes from 0f to 100f(real distor) AND making like switch or if statment or whatever which you can basicly do like if it's 0.0f - 10.0f it will asign liek 1 to it or just choos first hting if it's 10.0f - 12.0f then asign or choos 2 if it's 12.0f - 15.0f it's asign 3 or choos 3 AND AS YOU CAN SEE i put the same persent on chooseing as numbers above and that is how it's done(that is HOW you can implement precision for weapon like in world of tank OR ANY OTHER GAME!)
//  i don't know in what class in hierarcy put this function
void God::ShootAI(/*WeaponClass Weapon,*/ Vec3 MobPos/*,std::vector<*MobOld> AllMobs*/    )//this function should take these oarams( FIRST some weapon class to get precision for eacht unique weapon SECOND the pos of the mob(AI mob probably  OR one which we control as in strategy camera but not directly) THIRED all Mobs in the game(or literaly all or only shootable once!!!) )
{
	std::uniform_real_distribution<float> PercentRealDistribution(0, 100);
	std::random_device Seed; // don't know do i need 3 different random devices for every random number generator or not??? i don't know check it latrer tho!!!
	std::mt19937 RandomNumberGenerator(Seed());

	float PrecisionCircleRandomRegion = PercentRealDistribution(RandomNumberGenerator);
	float Min = 0.0f;
	float Max = 0.0f;

	// I can make some for loop AND iterate on some vector to make much more different acurecy aiming of weapon (for each weapon different)
	//for (Weapon)
	//{
		// do different acurecy of weapon
	//}
	if (PrecisionCircleRandomRegion >= 0.0f && PrecisionCircleRandomRegion <= 30.0f)  
	{
		Min = 0.0;
		Max = 0.01;
	}
	else if (PrecisionCircleRandomRegion >= 30.0f && PrecisionCircleRandomRegion <= 80.0f)  
	{
		Min = 0.01;
		Max = 0.05;
	}
	else if (PrecisionCircleRandomRegion >= 80.0f && PrecisionCircleRandomRegion <= 100.0f) 
	{
		Min = 0.05;
		Max = 0.3;
	}

	std::uniform_real_distribution<float> HitBoxRealDistribution(Min, Max); 
	std::uniform_int_distribution<int> SignBitDistribution(0, 1);
	 
	float RandomShootPitch = HitBoxRealDistribution(RandomNumberGenerator);
	float RandomShootYaw = HitBoxRealDistribution(RandomNumberGenerator);
	
	// check that i get all variations of signs equaly + + , - + , + - , - - , all 25% chanes
	// pitch and yaw are in INCORECT quadrents on quartision qoordinates where it shoudl be x and y positive it like both negative 
	if(SignBitDistribution(RandomNumberGenerator))
	{
		RandomShootPitch = -RandomShootPitch;
	}
	if(SignBitDistribution(RandomNumberGenerator))
	{
		RandomShootYaw = -RandomShootYaw;
	}

	/////////////
	/////////////
	/////////////
	/////////////
	/////////////
	/////////////
	//NOW here is the thing I NEED TO MAKE THIS FUNCTIONS actualy used by some AI sowhere where AI standa SO BASICLY i will need to give here AI pos 
	// SO i odn't realy knwo what i need form this funciton SO THINK ABOUT IT cos now you kinda dont' realy know whta this funciton shoudl do !! 
	/////////////
	/////////////
	/////////////
	/////////////
	/////////////
	/////////////

	/// IT'S STILL A BIT BUGY WITH AIMING FIX LATER (like even when i coment out random rotation IT WILL NOT shoot at corect targest all the time!) 
	/// it somtims shoots in much farther things than where it is
	/// MAY BE AIM A TRIG A BIT OFF OR TARRGEST A BIT OFF OR FLOTING POINT errors i don't konow
	// everytwhere is zomby insted use Mob and everywhere is arais of zombies insted use AllMobs (which is just array of mobs)
	Vec3 TargetPos;
	Vec3 MobDistanceVecTarget = { 99999999999999999999999999999999999999.0f ,99999999999999999999999999999999999999.0f ,99999999999999999999999999999999999999.0f };// use std::literals::float::max OR somthing like that cos just 999999 looks realy agly// WELL this cos i need first target be 100% farther OR I DOSNT' WORK AT ALL!!!  SOOO if my target will be double  on farther than this number AI WON'T SHOOT AT ALL!!! so watch out for bug IF YOU MAKE LIKE star wars battles cos it's HUUGE DISTANCE 
	for (int i = 0; i < Zombies->size(); i++)
	{
		Vec3 TargetPosTemp = Zombies->operator[](i).GetPosition();
		Vec3 MobDistanceVecTargetTemp = TargetPosTemp - MobPos;     
		if (MobDistanceVecTargetTemp.GetLengthSq() < MobDistanceVecTarget.GetLengthSq())
		{
			TargetPos = TargetPosTemp; 
			MobDistanceVecTarget = MobDistanceVecTargetTemp;
		}
	}

	float dX = MobPos.X - TargetPos.X; 
	float dY = MobPos.Y - TargetPos.Y;
	float dZ = MobPos.Z - TargetPos.Z;

	float Pitch = std::atan2(dY, std::sqrt(dX * dX + dZ * dZ));
	float Yaw = std::atan2(dX, dZ) + PI;
	 
	//Camera.SetCam((Pitch + RandomShootPitch), (Yaw + RandomShootYaw));// just for test deleet later(sets comera of the player at the same angle as ttarget)

	//Rotation MobRotation(Pitch, Yaw); // ideal precision(well if not count that it still misis somtims even with it!)
	Rotation MobRotation((Pitch + RandomShootPitch), (Yaw + RandomShootYaw));

	for (int i = 0; i < Zombies->size(); i++)
	{
  		Vec3 TargetPos = Zombies->operator[](i).GetPosition();
  		RayCast MobRay = RayCast(MobPos, MobRotation.Pitch, MobRotation.Yaw);  // You need initialize RayCast here cos if do only once befor the loop the variables values will stock up
  		for (float Step = 0.0f; Step < 225.0f/*25 original*/; Step += 0.1f)
  		{
  			auto[RayLocation, RayLocationCorrected] = MobRay.ShootARayCast();
  			/// if (std::floor(MobPos.Y) == std::round(RayLocation.X) && std::floor(MobPos.X) == std::round(RayLocation.Y) && std::floor(MobPos.Z) == std::round(RayLocation.Z))
  			if (TargetPos.X + 0.5f >= RayLocation.X && TargetPos.X - 0.5f <= RayLocation.X &&
  				TargetPos.Y + 0.5f >= RayLocation.Y && TargetPos.Y - 0.5f <= RayLocation.Y &&
  				TargetPos.Z + 0.5f >= RayLocation.Z && TargetPos.Z - 0.5f <= RayLocation.Z)
  			{
  				HealthState::Alive == Zombies->operator[](i).TakeDamage(Damage); // UNCOMENT THIS LINE is corect and good!
  				return;
  			}
		}
	}

}


///(END) ALL THIS SHOULD BE ONLY IN AI FOR MOBS AND NOT IN GOD(player) SO CUT IT LATER I JUST DO IT FOR THE TEST HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!