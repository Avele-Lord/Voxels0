// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "WindowsSafeIncluder.h" // need 
#include <queue> // need 
#include <optional> // need 
#include "Mouse.h" // need 


std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x,y };
}

std::optional<Mouse::RawDelta> Mouse::ReadRawDelta() noexcept
{
	if (RawDeltaBuffer.empty())
	{
		return std::nullopt;
	}
	const RawDelta Delta = RawDeltaBuffer.front();
	RawDeltaBuffer.pop();
	return Delta;
}


int Mouse::GetPosX() const noexcept
{
	return x;
}

int Mouse::GetPosY() const noexcept
{
	return y;
}

bool Mouse::IsInWindow() const noexcept
{
	return bIsInWindow;
}

bool Mouse::LeftIsPressed() const noexcept
{
	return bLeftIsPressed;
}

bool Mouse::RightIsPressed() const noexcept
{
	return bRightIsPressed;
}

std::optional<Mouse::Event> Mouse::Read() noexcept
{
	if (Buffer.size() > 0u)
	{
		Mouse::Event MouseBuffer = Buffer.front();
		Buffer.pop();
		return MouseBuffer;
	}
	return {};
}

void Mouse::Flush() noexcept
{
	Buffer = std::queue<Event>();
}

void Mouse::EnableRaw() noexcept
{
	bRawEnabled = true;
}

void Mouse::DisableRaw() noexcept
{
	bRawEnabled = false;
}

bool Mouse::RawEnabled() const noexcept
{
	return bRawEnabled;
}


void Mouse::OnMouseMove(int Newx, int Newy) noexcept
{
	x = Newx;
	y = Newy;

	Buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	TrimBuffer();
}

void Mouse::OnMouseLeave() noexcept
{
	bIsInWindow = false;
	Buffer.push(Mouse::Event(Mouse::Event::Type::Leave, *this));
	TrimBuffer();
}

void Mouse::OnMouseEnter() noexcept
{
	bIsInWindow = true;
	Buffer.push(Mouse::Event(Mouse::Event::Type::Enter, *this));
	TrimBuffer();
}

void Mouse::OnRawDelta(int DeltaX, int DeltaY) noexcept
{
	RawDeltaBuffer.push({ DeltaX,DeltaY });
	TrimBuffer();
}


void Mouse::OnLeftPressed(int x, int y) noexcept
{
	bLeftIsPressed = true;

	Buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	bLeftIsPressed = false;

	Buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	TrimBuffer();
}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	bRightIsPressed = true;

	Buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	TrimBuffer();
}

void Mouse::OnRightReleased(int x, int y) noexcept
{
	bRightIsPressed = false;

	Buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	Buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	Buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	TrimBuffer();
}

void Mouse::TrimBuffer() noexcept
{
	while (Buffer.size() > BufferSize)
	{
		Buffer.pop();
	}
}

void Mouse::TrimRawInputBuffer() noexcept
{
	while (RawDeltaBuffer.size() > BufferSize)
	{
		RawDeltaBuffer.pop();
	}
}


void Mouse::OnWheelDelta(int x, int y, int Delta) noexcept
{
	WheelDeltaCarry += Delta;
	// Generate events for every 120 
	while (WheelDeltaCarry >= WHEEL_DELTA)
	{
		WheelDeltaCarry -= WHEEL_DELTA;
		OnWheelUp(x, y);
	}
	while (WheelDeltaCarry <= -WHEEL_DELTA)
	{
		WheelDeltaCarry += WHEEL_DELTA;
		OnWheelDown(x, y);
	}
}