// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "Timer.h" // need 
#include "WindowsSafeIncluder.h" // need 
#pragma comment(lib, "winmm.lib" ) // I DON'T KNOW for what it is but if i comment this out everything is still working LEARN IT! 


Timer::Timer()
{
	unsigned long long Frequency;
	QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency);
	InvFreqMilli = 1.0f / (float)((double)Frequency / 1000.0);
	StartWatch();
}

void Timer::StopWatch()
{
	if (!WatchStopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&CurrentCount);
		WatchStopped = true;
	}
}

void Timer::StartWatch()
{
	WatchStopped = false;
	QueryPerformanceCounter((LARGE_INTEGER*)&StartCount);
}

float Timer::GetTimeSec() const
{
	return GetTimeMilli() / 1000.0f;
}

float Timer::GetTimeMilli() const
{
	if (!WatchStopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&CurrentCount);
		return (float)(CurrentCount - StartCount) * InvFreqMilli;
	}
	else
	{
		return (float)(CurrentCount - StartCount) * InvFreqMilli;
	}
}