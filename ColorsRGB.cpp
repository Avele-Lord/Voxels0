#include "ColorsRGB.h"
#include <random>
#include "ConstantsChunkGenerator.h"
#include <vector>
#include "Vec3.h"

//  Refactored start 20.05.2021
ColorsRGB::ColorsRGB(int Index)
{
	std::vector<Vec3> Colors;
	Colors.resize(CCG::NumberRealOfColors);
	StaticColor = false;









	/// Color Collection start


/// Dope Colors
//Colors[0] = Vec3((float)100 / (float)255, (float)50 / (float)255, (float)150 / (float)255);
//Colors[1] = Vec3((float)220 / (float)255, (float)30 / (float)255, (float)25 / (float)255);
//Colors[2] = Vec3((float)240 / (float)255, (float)190 / (float)255, (float)9 / (float)255);
//Colors[3] = Vec3((float)53 / (float)255, (float)150 / (float)255, (float)48 / (float)255);
//Colors[4] = Vec3((float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255);


	//Colors[0] = Vec3((float)100 / (float)255, (float)50 / (float)255, (float)150 / (float)255);
	//Colors[1] = Vec3((float)220 / (float)255, (float)30 / (float)255, (float)25 / (float)255);
	//Colors[2] = Vec3((float)130 / (float)255, (float)130 / (float)255, (float)130 / (float)255);
	//Colors[3] = Vec3((float)130 / (float)255, (float)130 / (float)255, (float)130 / (float)255);
	//Colors[4] = Vec3((float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255);


	//Colors[5] = Vec3((float)53 / (float)255, (float)150 / (float)255, (float)48 / (float)255);
	//Colors[6] = Vec3((float)110 / (float)255, (float)70 / (float)255, (float)40 / (float)255);
	//{(float)130 / (float)255, (float)130 / (float)255, (float)230 / (float)255},
	//{(float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255},


	//R = (float)53 / (float)255;
	//G = (float)150 / (float)255;
	//B = (float)48 / (float)255;
	//break;

	//	case 242:
	//		R = (float)110 / (float)255;
	//		G = (float)70 / (float)255;
	//		B = (float)40 / (float)255;
	//		break;

	//	case 243:
	//		R = (float)110 / (float)255;
	//		G = (float)70 / (float)255;
	//		B = (float)40 / (float)255;
	//		break;
	//	case 244:
	//		R = (float)10 / (float)255;
	//		G = (float)10 / (float)255;
	//		B = (float)10 / (float)255;





	/// Color Collection start














	/// Dope Colors
	//Colors[0] = Vec3((float)100 / (float)255, (float)50 / (float)255, (float)150 / (float)255);
	//Colors[1] = Vec3((float)220 / (float)255, (float)30 / (float)255, (float)25 / (float)255);
	//Colors[2] = Vec3((float)240 / (float)255, (float)190 / (float)255, (float)9 / (float)255);
	//Colors[3] = Vec3((float)53 / (float)255, (float)150 / (float)255, (float)48 / (float)255);
	//Colors[4] = Vec3((float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255);


	Colors[0] = Vec3((float)100 / (float)255, (float)50 / (float)255, (float)150 / (float)255);
	Colors[1] = Vec3((float)220 / (float)255, (float)30 / (float)255, (float)25 / (float)255);
	Colors[2] = Vec3((float)130 / (float)255, (float)130 / (float)255, (float)130 / (float)255);
	Colors[3] = Vec3((float)130 / (float)255, (float)130 / (float)255, (float)130 / (float)255);
	Colors[4] = Vec3((float)300 / (float)255, (float)300 / (float)255, (float)300 / (float)255);


	Colors[5] = Vec3((float)53 / (float)255, (float)150 / (float)255, (float)48 / (float)255);
	Colors[6] = Vec3((float)110 / (float)255, (float)70 / (float)255, (float)40 / (float)255);
	float ColorLayersCeiled = std::ceil(CCG::ColorLayers);
	float ColorLayersIndex = ColorLayersCeiled;
	if (Index < 241)
	{
		StaticColor = false;
		for (int i = 0; true; ColorLayersIndex += ColorLayersCeiled, i++)
		{
			if (Index < ColorLayersIndex)
			{
				if (!(i >= (int)Colors.size()))
				{
					R = Colors[i].X;
					G = Colors[i].Y;
					B = Colors[i].Z;
				}
				else
				{
					int Wrappedi = i % Colors.size();
					R = Colors[Wrappedi].X;
					G = Colors[Wrappedi].Y;
					B = Colors[Wrappedi].Z;
				}

				float MinColorSaturation = 0.5f;
				float ColorSaturation = MinColorSaturation + (float)(Index % (int)ColorLayersCeiled) / ColorLayersCeiled;

				R *= ColorSaturation;
				G *= ColorSaturation;
				B *= ColorSaturation;
				break;
			}
		}
	}
	else if (Index >= 241)
	{
		switch (Index)
		{
		case 241:
			R = (float)53 / (float)255;
			G = (float)150 / (float)255;
			B = (float)48 / (float)255;
			break;

		case 242:
			R = (float)110 / (float)255;
			G = (float)70 / (float)255;
			B = (float)40 / (float)255;
			break;

		case 243:
			R = (float)110 / (float)255;
			G = (float)70 / (float)255;
			B = (float)40 / (float)255;
			break;
		case 244:
			R = (float)10 / (float)255;
			G = (float)10 / (float)255;
			B = (float)10 / (float)255;
			StaticColor = true;
			break;

		default:
			break;
		}

	}
}

 void ColorsRGB::RandomizeCurrentColor()
{
	float ColorRange = 0.1f;
	if (StaticColor)
	{
		ColorRange = 0.01f;
	}

	std::uniform_real_distribution<float> Range(0.0f, /*0.1f*/ColorRange);

	std::random_device SeedR;
	std::mt19937 RandomNumberGeneratorR(SeedR());
	float RandomNumberR = Range(RandomNumberGeneratorR);

	std::random_device SeedG;
	std::mt19937 RandomNumberGeneratorG(SeedG());
	float RandomNumberG = Range(RandomNumberGeneratorG);

	std::random_device SeedB;
	std::mt19937 RandomNumberGeneratorB(SeedB());
	float RandomNumberB = Range(RandomNumberGeneratorB);

	R += RandomNumberR;
	G += RandomNumberG;
	B += RandomNumberB;
	
}
//  Refactored end 20.05.2021