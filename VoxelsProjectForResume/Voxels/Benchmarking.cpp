#include "Benchmarking.h"

///  Refactored start 15.04.2021
Benchmark::Benchmark()
{
	Start = std::chrono::high_resolution_clock::now();
}

Benchmark::~Benchmark()
{
	End = std::chrono::high_resolution_clock::now();
	Duration = End - Start;
	float MS = Duration.count() * 1000.0f;
}

float Benchmark::Stop()
{
	End = std::chrono::high_resolution_clock::now();
	Duration = End - Start;
	float MS = Duration.count() * 1000.0f;
	return MS;
}
///  Refactored end 15.04.2021