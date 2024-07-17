#pragma once
// Refactored 14.04.2021	// Looked Through 15.09.2021
#include <queue> // need 
#include <bitset> // need 
#include <optional> // need 


class Keyboard
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
		};
	private:
		Type AType;
		unsigned char Code;
	public:
		Event(Type Type, unsigned char Code) noexcept
			:
			AType(Type),
			Code(Code)
		{}
		bool IsPress() const noexcept
		{
			return AType == Type::Press;
		}
		bool IsRelease() const noexcept
		{
			return AType == Type::Release;
		}
		unsigned char GetCode() const noexcept
		{
			return Code;
		}
	};
public:
	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator=(const Keyboard&) = delete;
	// Key event stuff
	bool KeyIsPressed(unsigned char KeyCode) const noexcept;
	std::optional<Event> ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;
	// Char event stuff
	std::optional<char> ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;
	// Autorepeat control
	void EnableAutorepeat() noexcept;
	void DisableAutorepeat() noexcept;
	bool AutorepeatIsEnabled() const noexcept;
private:
	void OnKeyPressed(unsigned char KeyCode) noexcept;
	void OnKeyReleased(unsigned char KeyCode) noexcept;
	void OnChar(char Character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& Buffer) noexcept;
private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int BufferSize = 16u;
	bool AutorepeatEnabled = false;
	std::bitset<nKeys> KeyStates;
	std::queue<Event> KeyBuffer;
	std::queue<char> CharBuffer;
};