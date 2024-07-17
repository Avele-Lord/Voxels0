// Refactored 20.05.2021	// Looked Through 15.09.2021
#include <tuple> // need
#include "RayCast.h" // need
#include "ConstantsChunkGenerator.h" // need
#include <cmath> // need


/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// DUDE reneme what this class takes and riters AND EXECTLY everywhere where it's EndLocation IT'S ACTUALY START LOCATION and in class itself pass not call EndLocation BUT or start location OR omthing like MobPos or CharactrePos BUT NOT EndLocation!!!
/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
RayCast::RayCast(Vec3 EndLocation, float Pitch, float Yaw)
	:
	EndLocation(EndLocation),
	Pitch(Pitch),
	Yaw(Yaw)
	
{}

std::pair<Vec3, Vec3> RayCast::ShootARayCast()
{
	EndLocation.X += (std::sin(Yaw) * std::cos(Pitch)) * 0.1f; 
	EndLocation.Y += -std::sin(Pitch) * 0.1f;
	EndLocation.Z += (std::cos(Yaw) * std::cos(Pitch)) * 0.1f; 


	//Vec2TD EndLocationCorrectedBug;
	Vec3 EndLocationCorrected; // i need to move this culculations if it's less than 0 to where it's acutaly used COS raycast noto nly about chunks! 
	if (EndLocation.X < 0)
	{
		EndLocationCorrected.X = EndLocation.X - (float)(ChunkDimensionsLength - 1);
	}
	else
	{
		EndLocationCorrected.X = EndLocation.X;
	}
	
	
	if (EndLocation.Y < 0)
	{
		EndLocationCorrected.Y = EndLocation.Y - (float)(ChunkDimensionsLength - 1);
	}
	else
	{
		EndLocationCorrected.Y = EndLocation.Y;
	}


	if (EndLocation.Z < 0)
	{
		EndLocationCorrected.Z = EndLocation.Z - (float)(ChunkDimensionsLength - 1);
	}
	else
	{
		EndLocationCorrected.Z = EndLocation.Z;
	}


	return { EndLocation, EndLocationCorrected };
}

Vec3 RayCast::GetEndLocation()
{
	return EndLocation;
}