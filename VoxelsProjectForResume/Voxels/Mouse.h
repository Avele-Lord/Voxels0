#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021
#include <queue> // need 
#include <optional> // need 


class Mouse
{
	friend class Window;
public:
	struct RawDelta
	{
		int x, y;
	};
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
		};
	private:
		Type AType;
		bool bLeftIsPressed;
		bool bRightIsPressed;
		int x;
		int y;
	public:
		Event(Type Type, const Mouse& Parent) noexcept
			:
			AType(Type),
			bLeftIsPressed(Parent.bLeftIsPressed),
			bRightIsPressed(Parent.bRightIsPressed),
			x(Parent.x),
			y(Parent.y)
		{}
		Type GetType() const noexcept
		{
			return AType;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return{ x,y };
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool LeftIsPressed() const noexcept
		{
			return bLeftIsPressed;
		}
		bool RightIsPressed() const noexcept
		{
			return bRightIsPressed;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> GetPos() const noexcept;
	std::optional<RawDelta> ReadRawDelta() noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	std::optional<Mouse::Event> Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return Buffer.empty();
	}
	void Flush() noexcept;
	void EnableRaw() noexcept;
	void DisableRaw() noexcept;
	bool RawEnabled() const noexcept;
private:
	void OnMouseMove(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnRawDelta(int DeltaX, int DeltaY) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
	void TrimRawInputBuffer() noexcept;
	void OnWheelDelta(int x, int y, int Delta) noexcept;
private:
	static constexpr unsigned int BufferSize = 16u;
	int x;
	int y;
	bool bLeftIsPressed = false;
	bool bRightIsPressed = false;
	bool bIsInWindow = false;
	int WheelDeltaCarry = 0;
	bool bRawEnabled = false;
	std::queue<Event> Buffer;
	std::queue<RawDelta> RawDeltaBuffer;
};