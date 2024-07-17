#pragma once

#include<chrono>

//  Refactored start 13.04.2021
class Benchmark
{
public:
	Benchmark();
	~Benchmark();
	float Stop();
protected:

private:



public:

protected:

private:
	std::chrono::time_point<std::chrono::steady_clock> Start;
	std::chrono::time_point<std::chrono::steady_clock> End;
	std::chrono::duration<float> Duration;
};
//  Refactored end 13.04.2021