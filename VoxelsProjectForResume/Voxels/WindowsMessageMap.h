#pragma once
#include <unordered_map>
#include "Win.h"

///  Refactored start 15.04.2021
class WindowsMessageMap
{
public:
	WindowsMessageMap() noexcept;
	std::string operator()(DWORD Msg, LPARAM LP, WPARAM WP) const noexcept;
private:
	std::unordered_map<DWORD, std::string> Map;
};
///  Refactored end 15.04.2021