// Refactored 15.04.2021(NON Refactored)	// Looked Through 15.04.2021
#include "Graphics.h"  // need 
#include "dxerr.h" // need 
#include "GraphicsThrowMacros.h" // need 
#include "imgui/imgui_impl_dx11.h" // need 
#include "imgui/imgui_impl_win32.h" // need 
#include <sstream> // need 


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")


Graphics::Graphics(HWND hWnd, int Width, int Height)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0 /* DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH*/;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// for checking results of d3d functions
	HRESULT HR;

	// create device and front/back buffers, and swap chain and rendering context
	GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE/* D3D_DRIVER_TYPE_REFERENCE*/ /*D3D_DRIVER_TYPE_WARP*/,
		nullptr,
		0 /* swapCreateFlags*//*D3D11_CREATE_DEVICE_DEBUG*/,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	)); // I did
	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GFX_THROW_INFO(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
	GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	GFX_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

	// bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stensil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = Width;
	descDepth.Height = Height;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	GFX_THROW_INFO(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	GFX_THROW_INFO(pDevice->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pDSV
	));

	// bind depth stensil view to OM
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = (float)Width;
	vp.Height = (float)Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vp);

	// init imgui d3d impl
	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());

	//pSwap->SetFullscreenState(TRUE, nullptr);
}

Graphics::~Graphics()
{
	//pSwap->SetFullscreenState(FALSE, nullptr);
	ImGui_ImplDX11_Shutdown();
}

void Graphics::EndFrame()
{
	// imgui frame end
	if (ImguiEnabled)
	{
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	HRESULT HR;
#ifndef NDEBUG
	InfoManager.Set();
#endif
	if (FAILED(HR = pSwap->Present(/*1u*/4u, 0u)))
	{
		if (HR == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			throw GFX_EXCEPT(HR);
		}
	}
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept
{
	// imgui begin frame
	if (ImguiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(UINT IndexCount) noexcept(!IS_DEBUG)
{
	GFX_THROW_INFO_ONLY(pContext->DrawIndexed(IndexCount, 0u, 0u));
}

void Graphics::DrawInstanced(UINT IndexCount, UINT InstanceCount) noexcept(!IS_DEBUG)
{
	GFX_THROW_INFO_ONLY(pContext->DrawIndexedInstanced(IndexCount, InstanceCount, 0u, 0u, 0u));
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	Projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
	return Projection;
}

void Graphics::SetCamera(DirectX::FXMMATRIX cam) noexcept
{
	Camera = cam;
}

DirectX::XMMATRIX Graphics::GetCamera() const noexcept
{
	return Camera;
}

void Graphics::EnableImgui() noexcept
{
	ImguiEnabled = true;
}

void Graphics::DisableImgui() noexcept
{
	ImguiEnabled = false;
}

bool Graphics::IsImguiEnabled() const noexcept
{
	return ImguiEnabled;
}


// Graphics exception stuff
Graphics::HrException::HrException(int line, const char * file, HRESULT HR, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file),
	HR(HR)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		Info += m;
		Info.push_back('\n');
	}
	// remove final newline if exists
	if (!Info.empty())
	{
		Info.pop_back();
	}
}

const char* Graphics::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if (!Info.empty())
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	WhatBuffer = oss.str();
	return WhatBuffer.c_str();
}

const char* Graphics::HrException::GetType() const noexcept
{
	return "Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept
{
	return HR;
}

std::string Graphics::HrException::GetErrorString() const noexcept
{
	return DXGetErrorString(HR);
}

std::string Graphics::HrException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(HR, buf, sizeof(buf));
	return buf;
}

std::string Graphics::HrException::GetErrorInfo() const noexcept
{
	return Info;
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
Graphics::InfoException::InfoException(int line, const char * file, std::vector<std::string> infoMsgs) noexcept
	:
	Exception(line, file)
{
	// join all info messages with newlines into single string
	for (const auto& m : infoMsgs)
	{
		Info += m;
		Info.push_back('\n');
	}
	// remove final newline if exists
	if (!Info.empty())
	{
		Info.pop_back();
	}
}


const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	WhatBuffer = oss.str();
	return WhatBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept
{
	return "Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return Info;
}