// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "Window.h"  // need 
#include "Graphics.h"  // need 
#include <sstream>  // need 
#include "resource.h"  // need 
#include "WindowsThrowMacros.h"  // need 
#include "imgui/imgui_impl_win32.h"  // need 


// Window Class Stuff
Window::WindowClass Window::WindowClass::WndClass;

Window::WindowClass::WindowClass() noexcept
	:
	HInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX WC = { 0 };
	WC.cbSize = sizeof(WC);
	WC.style = CS_OWNDC;
	WC.lpfnWndProc = HandleMsgSetup;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = GetInstance();
	WC.hIcon = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 32, 32, 0
	));
	WC.hCursor = nullptr;
	WC.hbrBackground = nullptr;
	WC.lpszMenuName = nullptr;
	WC.lpszClassName = GetName();
	WC.hIconSm = static_cast<HICON>(LoadImage(
		GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 16, 16, 0
	));
	RegisterClassEx(&WC);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(WndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return WndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return WndClass.HInst;
}


// Window Stuff
Window::Window(int Width, int Height, const char* Name)
	:
	Width(Width),
	Height(Height)
{
	// Calculate window size based on desired client region size
	RECT WR;
	WR.left = 100;
	WR.right = Width + WR.left;
	WR.top = 100;
	WR.bottom = Height + WR.top;
	if (AdjustWindowRect(&WR, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
	// Create window & get HWnd
	HWnd = CreateWindow(
		WindowClass::GetName(), Name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		/*CW_USEDEFAULT*/ -8, /* CW_USEDEFAULT*/ -31, WR.right - WR.left, WR.bottom - WR.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	// Check for error
	if (HWnd == nullptr)
	{
		throw CHWND_LAST_EXCEPT();
	}
	// Newly created windows start off as hidden
	ShowWindow(HWnd, SW_SHOWDEFAULT);
	// Init ImGui Win32 Impl
	ImGui_ImplWin32_Init(HWnd);
	// Create graphics object
	pGfx = std::make_unique<Graphics>(HWnd, Width, Height);
	// Register	mouse raw input device
	RAWINPUTDEVICE Rid;
	Rid.usUsagePage = 0x01; // Mouse page
	Rid.usUsage = 0x02; // Mouse usage
	Rid.dwFlags = 0;
	Rid.hwndTarget = nullptr;
	if (RegisterRawInputDevices(&Rid, 1, sizeof(Rid)) == FALSE)
	{
		throw CHWND_LAST_EXCEPT();
	}
}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(HWnd);
}

void Window::SetTitle(const std::string& Title)
{
	if (SetWindowText(HWnd, Title.c_str()) == 0)
	{
		throw CHWND_LAST_EXCEPT();
	}
}

void Window::EnableCursor() noexcept
{
	bCursorEnabled = true;
	ShowCursor();
	EnableImGuiMouse();
	FreeCursor();
}

void Window::DisableCursor() noexcept
{
	bCursorEnabled = false;
	HideCursor();
	DisableImGuiMouse();
	ConfineCursor();
}

bool Window::CursorEnabled() const noexcept
{
	return bCursorEnabled;
}


std::optional<int> Window::ProcessMessages() noexcept
{
	MSG Msg;
	// While queue has messages, remove and dispatch them (but do not block on empty queue)
	while (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
	{
		// Check for quit because peekmessage does not signal this via return val
		if (Msg.message == WM_QUIT)
		{
			// Return optional wrapping int (arg to PostQuitMessage is in WParam) signals quit
			return (int)Msg.wParam;
		}

		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	// Return empty optional when not quitting app
	return {};
}

Graphics& Window::Gfx()
{
	if (!pGfx)
	{
		throw CHWND_NOGFX_EXCEPT();
	}
	return *pGfx;
}

void Window::ConfineCursor() noexcept
{
	RECT Rect;
	GetClientRect(HWnd, &Rect);
	MapWindowPoints(HWnd, nullptr, reinterpret_cast<POINT*>(&Rect), 2);
	ClipCursor(&Rect);
}

void Window::FreeCursor() noexcept
{
	ClipCursor(nullptr);
}



void Window::HideCursor() noexcept
{
	while (::ShowCursor(FALSE) >= 0);
}

void Window::ShowCursor() noexcept
{
	while (::ShowCursor(TRUE) < 0);
}

void Window::EnableImGuiMouse() noexcept
{
	ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
}

void Window::DisableImGuiMouse() noexcept
{
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
}



LRESULT CALLBACK Window::HandleMsgSetup(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept
{
	// Use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (Msg == WM_NCCREATE)
	{
		// Extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(LParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// Set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(HWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(HWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// Forward message to window instance handler
		return pWnd->HandleMsg(HWnd, Msg, WParam, LParam);
	}
	// If we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(HWnd, Msg, WParam, LParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept
{
	// Retrieve ptr to window instance
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(HWnd, GWLP_USERDATA));
	// Forward message to window instance handler
	return pWnd->HandleMsg(HWnd, Msg, WParam, LParam);
}

LRESULT Window::HandleMsg(HWND HWnd, UINT Msg, WPARAM WParam, LPARAM LParam) noexcept
{
	if (ImGui_ImplWin32_WndProcHandler(HWnd, Msg, WParam, LParam))
	{
		return true;
	}
	const auto& Imio = ImGui::GetIO();

	switch (Msg)
	{
		// We don't want the DefProc to handle this message because
		// We want our destructor to destroy the window, so return 0 instead of break
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		// Clear keystate when window loses focus to prevent input getting "stuck"
	case WM_KILLFOCUS:
		Keyboard.ClearState();
		break;
	case WM_ACTIVATE:
		// Confine/free cursor on window to foreground/background if cursor disabled
		if (!bCursorEnabled)
		{
			if (WParam & WA_ACTIVE)
			{
				ConfineCursor();
				HideCursor();
			}
			else
			{
				FreeCursor();
				ShowCursor();
			}
		}
		break;

		/*********** KEYBOARD MESSAGES ***********/
	case WM_KEYDOWN:
		// Syskey commands need to be handled to track ALT key (VK_MENU) and F10
	case WM_SYSKEYDOWN:
		// Stifle this keyboard message if imgui wants to capture
		if (Imio.WantCaptureKeyboard)
		{
			break;
		}
		if (!(LParam & 0x40000000) || Keyboard.AutorepeatIsEnabled()) // Filter autorepeat
		{
			Keyboard.OnKeyPressed(static_cast<unsigned char>(WParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		// Stifle this keyboard message if imgui wants to capture
		if (Imio.WantCaptureKeyboard)
		{
			break;
		}
		Keyboard.OnKeyReleased(static_cast<unsigned char>(WParam));
		break;
	case WM_CHAR:
		// Stifle this keyboard message if imgui wants to capture
		if (Imio.WantCaptureKeyboard)
		{
			break;
		}
		Keyboard.OnChar(static_cast<unsigned char>(WParam));
		break;
		/*********** END KEYBOARD MESSAGES ***********/

		/************* MOUSE MESSAGES ****************/
	case WM_MOUSEMOVE:
	{
		const POINTS Points = MAKEPOINTS(LParam);
		// Cursorless exclusive gets first dibs
		if (!bCursorEnabled)
		{
			if (!Mouse.IsInWindow())
			{
				SetCapture(HWnd);
				Mouse.OnMouseEnter();
				HideCursor();
			}
			break;
		}
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}

		// In client region -> log move, and log enter + capture mouse (if not previously in window)
		if (Points.x >= 0 && Points.x < Width && Points.y >= 0 && Points.y < Height)
		{
			Mouse.OnMouseMove(Points.x, Points.y);
			if (!Mouse.IsInWindow())
			{
				SetCapture(HWnd);
				Mouse.OnMouseEnter();
			}
		}
		// Not in client -> log move / maintain capture if button down
		else
		{
			if (WParam & (MK_LBUTTON | MK_RBUTTON))
			{
				Mouse.OnMouseMove(Points.x, Points.y);
			}
			// Button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				Mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		SetForegroundWindow(HWnd);
		if (!bCursorEnabled)
		{
			ConfineCursor();
			HideCursor();
		}
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS Points = MAKEPOINTS(LParam);
		Mouse.OnLeftPressed(Points.x, Points.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS Points = MAKEPOINTS(LParam);
		Mouse.OnRightPressed(Points.x, Points.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS Points = MAKEPOINTS(LParam);
		Mouse.OnLeftReleased(Points.x, Points.y);
		// Release mouse if outside of window
		if (Points.x < 0 || Points.x >= Width || Points.y < 0 || Points.y >= Height)
		{
			ReleaseCapture();
			Mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS Points = MAKEPOINTS(LParam);
		Mouse.OnRightReleased(Points.x, Points.y);
		// Release mouse if outside of window
		if (Points.x < 0 || Points.x >= Width || Points.y < 0 || Points.y >= Height)
		{
			ReleaseCapture();
			Mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		// Stifle this mouse message if imgui wants to capture
		if (Imio.WantCaptureMouse)
		{
			break;
		}
		const POINTS Points = MAKEPOINTS(LParam);
		const int Delta = GET_WHEEL_DELTA_WPARAM(WParam);
		Mouse.OnWheelDelta(Points.x, Points.y, Delta);
		break;
	}
	/************** END MOUSE MESSAGES **************/


	/************** RAW MOUSE MESSAGES **************/
	case WM_INPUT:
	{
		if (!Mouse.RawEnabled())
		{
			break;
		}
		UINT Size;
		// First get the size of the input data
		if (GetRawInputData(
			reinterpret_cast<HRAWINPUT>(LParam),
			RID_INPUT,
			nullptr,
			&Size,
			sizeof(RAWINPUTHEADER)) == -1)
		{
			// Bail msg processing if error
			break;
		}
		RawBuffer.resize(Size);
		// Read in the input data
		if (GetRawInputData(
			reinterpret_cast<HRAWINPUT>(LParam),
			RID_INPUT,
			RawBuffer.data(),
			&Size,
			sizeof(RAWINPUTHEADER)) != Size)
		{
			// Bail msg processing if error
			break;
		}
		// Process the raw input data
		auto& RawInput = reinterpret_cast<const RAWINPUT&>(*RawBuffer.data());
		if (RawInput.header.dwType == RIM_TYPEMOUSE &&
			(RawInput.data.mouse.lLastX != 0 || RawInput.data.mouse.lLastY != 0))
		{
			Mouse.OnRawDelta(RawInput.data.mouse.lLastX, RawInput.data.mouse.lLastY);
		}
		break;
	}
	/************** END RAW MOUSE MESSAGES **************/
	}

	return DefWindowProc(HWnd, Msg, WParam, LParam);
}


// Window Exception Stuff
std::string Window::Exception::TranslateErrorCode(HRESULT HR) noexcept
{
	char* pMsgBuf = nullptr;
	// Windows will allocate memory for err string and make our pointer point to it
	const DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, HR, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// Copy error string from windows-allocated buffer to std::string
	std::string ErrorString = pMsgBuf;
	// Free windows buffer
	LocalFree(pMsgBuf);
	return ErrorString;
}


Window::HrException::HrException(int Line, const char* File, HRESULT HR) noexcept
	:
	Exception(Line, File),
	HR(HR)
{}

const char* Window::HrException::what() const noexcept
{
	std::ostringstream OStringStream;
	OStringStream << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	WhatBuffer = OStringStream.str();
	return WhatBuffer.c_str();
}

const char* Window::HrException::GetType() const noexcept
{
	return "Window Exception";
}

HRESULT Window::HrException::GetErrorCode() const noexcept
{
	return HR;
}

std::string Window::HrException::GetErrorDescription() const noexcept
{
	return Exception::TranslateErrorCode(HR);
}


const char* Window::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics]";
}