#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021


class Timer
{
public:
	Timer();
	void StartWatch();
	void StopWatch();
	float GetTimeMilli() const;
	float GetTimeSec() const;
private:
	float InvFreqMilli;
	bool WatchStopped;
	unsigned long long CurrentCount;
	unsigned long long StartCount;
};