// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "Voxels.h" // need 
#include <string> // leanirng 2024



void InsertionSort(int Array[], int Size);
double MyPow(double x, int n);
double MyPow2(double x, int n);
double MyPow3(double x, int n);
double MyPow3Helper(double x, int n);



int CALLBACK WinMain(
	HINSTANCE HInstance,
	HINSTANCE HPrevInstance,
	LPSTR     LpCmdLine,
	int       nCmdShow)
{


	const int Size = 20;
	int Array[Size] = { 89, -8777, 0, 0 ,798 , 999, 765, 66, 78, 3, 6, 9, 1, 65, 32, 777, 1, 0, -343, 5897 };

	InsertionSort(Array, Size);

	//Array;
	std::string STR;
	
	for (int i = 0; i < Size; i++)
	{
		STR.append(std::to_string(Array[i]).c_str());
		STR.push_back(' ');
	}
	MessageBox(nullptr, STR.c_str(), "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);


	double POWERED = MyPow3(2.00000, 16);
	std::string STR2;
	STR2 = std::to_string(POWERED);


	MessageBox(nullptr, STR2.c_str(), "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);

	try
	{
		return Voxels{}.Go();
	}
	catch (const RootException& RootException)
	{
		MessageBox(nullptr, RootException.what(), RootException.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& Exception)
	{
		MessageBox(nullptr, Exception.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}



void InsertionSort(int* Array, int Size)
{
	for (int i = 1; i < Size; i++)
	{
		int IntTemp = Array[i];
		int j = i - 1;
		while (Array[j] > IntTemp && j >= 0)
		{
			Array[j + 1] = Array[j];
			j--;
		}
		Array[j + 1] = IntTemp;

		//for (int j = i; j < 0; j--)
		//{
		//	if (Array[j - 1] > IntTemp)
		//	{
		//		Array[j] = Array[j - 1];
		//	}
		//	else
		//	{
		//		Array[j] = IntTemp;
		//	}
		//}
	}
}

double MyPow(double Base, int Exponent)
{
	double Number = Base;
	if (Exponent > 0)
	{
		for (int i = 0; i < Exponent - 1; i++)
		{
			Number = Number * Base;
		}
	}
	else if (Exponent < 0)
	{
		Exponent = -Exponent;
		for (int i = 0; i < Exponent + 1; i++)
		{
			Number = Number / Base;
		}
	}
	else
	{
		Number = 1;
	}
	return Number;
}


double MyPow2(double Base, int Exponent)
{
	double Number = Base;

	
	if (Exponent == 0)
	{
		return 1;
	}
	else if (Exponent > 0)
	{
		return Base * MyPow2(Base, Exponent - 1);

		//for (int i = 0; i < Exponent - 1; i++)
		//{
		//	Number = Number * Base;
		//}
	}
	else if (Exponent < 0)
	{
		return MyPow2(Base, Exponent + 1) / Base;
		//return Base / MyPow2(Base, Exponent + 1);
		//Exponent = -Exponent;
		//for (int i = 0; i < Exponent + 1; i++)
		//{
		//	Number = Number / Base;
		//}
	}

	return Number;
}



double MyPow3(double Base, int Exponent)
{
	//return MyPow3Helper(Base, Exponent - 1);

	if (Exponent == 0) return 1;
	if (Exponent == 1) return Base;

	int Temp = MyPow3(Base, Exponent / 2);

	if (0 == (Exponent % 2))
	{
		//return MyPow3Helper(Base, Exponent / 2) * MyPow3Helper(Base, Exponent / 2);
		return Temp * Temp;

	}
	else
	{
		//return Base * MyPow3Helper(Base, Exponent / 2) * MyPow3Helper(Base, Exponent / 2);
		return Base * Temp * Temp;

	}
}

double MyPow3Helper(double Base, int Exponent)
{
	return 0.0f;
}
