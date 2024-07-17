#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "WindowsSafeIncluder.h"  // need 
#include <wrl.h>  // need 
#include <vector>  // need 
#include <dxgidebug.h>  // need 
#include <string> // 2023CH


class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long Next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};