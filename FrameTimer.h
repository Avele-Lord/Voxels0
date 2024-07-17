#pragma once
// Refactored 29.04.2021	// Looked Through 15.09.2021
#include "Timer.h" // need 
//#include <float.h> // Don't delete for now
#include <sstream> // need 
//#include <iomanip> // Don't delete for now


class FrameTimer
{
public:
	FrameTimer()
		:
		TimeMin(FLT_MAX),
		TimeMax(0.0f),
		TimeSum(0.0f),
		LastMin(0.0f),
		LastMax(0.0f),
		LastAvg(0.0f),
		FrameCount(0)
	{}
	void StartFrame()
	{
		Timer.StartWatch();
	}
	bool StopFrame()
	{
		Timer.StopWatch();
		const float FrameTime = Timer.GetTimeMilli();
		TimeSum += FrameTime;
		TimeMin = std::min(TimeMin, FrameTime);
		TimeMax = std::max(TimeMax, FrameTime);
		FrameCount++;
		if (FrameCount < NumFramesAvg)
		{
			return false;
		}
		else
		{
			LastAvg = TimeSum / (float)NumFramesAvg;
			LastMin = TimeMin;
			LastMax = TimeMax;
			TimeSum = 0.0f;
			TimeMin = FLT_MAX;
			TimeMax = 0.0f;
			FrameCount = 0;
			return true;
		}
	}
	template< class T >
	bool StopFrame(T& Output)
	{
		if (!StopFrame())
		{
			return false;
		}
		else
		{
			std::wstringstream StringStream;
			StringStream.precision(3);
			StringStream << L"Avg: [" << std::fixed << GetAvg() << L"] Min: [" << GetMin()
				<< L"] Max: [" << GetMax() << L"]" << std::endl;
			Output << StringStream.str();
			return true;
		}
	}
	float GetAvg() const
	{
		return LastAvg;
	}
	float GetMin() const
	{
		return LastMin;
	}
	float GetMax() const
	{
		return LastMax;
	}

private:
	const int NumFramesAvg = 20;
	Timer Timer;
	float TimeSum;
	float TimeMin;
	float TimeMax;
	int FrameCount;
	float LastMin;
	float LastMax;
	float LastAvg;
};