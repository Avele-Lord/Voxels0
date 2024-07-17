#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "WindowsSafeIncluder.h" // need 
#include "RootException.h" // need 
#include "Keyboard.h"  // need 
#include "Mouse.h" // need 
#include <memory> // 2023CH


class Window
{
public:
	class Exception : public RootException
	{
		using RootException::RootException;
	public:
		static std::string TranslateErrorCode(HRESULT HR) noexcept;
	};
	class HrException : public Exception
	{
	public:
		HrException(int Line, const char* File, HRESULT HR) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorDescription() const noexcept;
	private:
		HRESULT HR;
	};
	class NoGfxException : public Exception
	{
	public:
		using Exception::Exception;
		const char* GetType() const noexcept override;
	};
private:
	// Singleton manages registration/cleanup of window class
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* WndClassName = "Voxels";
		static WindowClass WndClass;
		HINSTANCE HInst;
	};
public:
	Window(int Width, int Height, const char* Name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& Title);
	void EnableCursor() noexcept;
	void DisableCursor() noexcept;
	bool CursorEnabled() const noexcept;
	static std::optional<int> ProcessMessages() noexcept;
	class Graphics& Gfx();
private:
	void ConfineCursor() noexcept;
	void FreeCursor() noexcept;
	void ShowCursor() noexcept;
	void HideCursor() noexcept;
	void EnableImGuiMouse() noexcept;
	void DisableImGuiMouse() noexcept;
	static LRESULT CALLBACK HandleMsgSetup(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept;
	static LRESULT CALLBACK HandleMsgThunk(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept;
	LRESULT HandleMsg(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept;
public:
	Keyboard Keyboard;
	Mouse Mouse;
private:
	bool bCursorEnabled = true;
	int Width;
	int Height;
	HWND HWnd;
	std::unique_ptr<class Graphics> pGfx;
	std::vector<BYTE> RawBuffer;
};