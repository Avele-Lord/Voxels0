// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "SmallTimer.h" // need 


using namespace std::chrono;

SmallTimer::SmallTimer() noexcept
{
	Last = steady_clock::now();
}

float SmallTimer::Mark() noexcept
{
	const auto Old = Last;
	Last = steady_clock::now();
	const duration<float> FrameTime = Last - Old;
	return FrameTime.count();
}

float SmallTimer::Peek() const noexcept
{
	return duration<float>(steady_clock::now() - Last).count();
}