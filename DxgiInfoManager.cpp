// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "DxgiInfoManager.h"  // need 
#include "Window.h"  // need 
#include "Graphics.h" // need 
#include "GraphicsThrowMacros.h"  // need 
#include "WindowsThrowMacros.h"  // need 


#pragma comment(lib, "dxguid.lib")


DxgiInfoManager::DxgiInfoManager()
{
	// Define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void **);

	// Load the dll that contains the function DXGIGetDebugInterface
	const auto HModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (HModDxgiDebug == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}

	// Get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(HModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}

	HRESULT HR;
	GFX_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pDxgiInfoQueue));
}

void DxgiInfoManager::Set() noexcept
{
	// Set the index (next) so that the next all to GetMessages()
	// Will only get errors generated after this call
	Next = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfoManager::GetMessages() const
{
	std::vector<std::string> Messages;
	const auto End = pDxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = Next; i < End; i++)
	{
		HRESULT HR;
		SIZE_T MessageLength;
		// Get the size of message i in bytes
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &MessageLength));
		// Allocate memory for message
		auto Bytes = std::make_unique<byte[]>(MessageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(Bytes.get());
		// Get the message and push its description into the vector
		GFX_THROW_NOINFO(pDxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &MessageLength));
		Messages.emplace_back(pMessage->pDescription);
	}
	return Messages;
}