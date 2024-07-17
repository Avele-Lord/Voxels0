#pragma once
// Refactored 14.04.2021	// Looked Through 15.09.2021
#include <chrono> // need 


class SmallTimer
{
public:
	SmallTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	std::chrono::steady_clock::time_point Last;
};