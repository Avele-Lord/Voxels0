#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "WindowsSafeIncluder.h" // need 
#include "RootException.h" // need 
#include "DxgiInfoManager.h"  // need  IN DEBUG MODE
#include <d3d11.h> // need 
#include <wrl.h>  // need 
#include <vector> // need 
#include <DirectXMath.h> // need 
#include <memory> // 2023CH
#include <stdexcept> // 2023CH
#include <string> // 2023CH


class Graphics
{
	friend class Voxel;
	friend class Chunk;
public:
	class Exception : public RootException
	{
		using RootException::RootException;
	};
	class HrException : public Exception
	{
	public:
		HrException(int Line, const char* File, HRESULT HR, std::vector<std::string> InfoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT HR;
		std::string Info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int Line, const char* File, std::vector<std::string> InfoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string Info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string Reason;
	};
public:
	Graphics(HWND HWnd, int Width, int Height);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float Red, float Green, float Blue) noexcept;
	void DrawIndexed(UINT IndexCount) noexcept(!IS_DEBUG);
	void DrawInstanced(UINT IndexCount, UINT InstanceCount) noexcept(!IS_DEBUG);
	void SetProjection(DirectX::FXMMATRIX Proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX Cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
private:
	DirectX::XMMATRIX Projection;
	DirectX::XMMATRIX Camera;
	bool ImguiEnabled = true;
#ifndef NDEBUG
	DxgiInfoManager InfoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};