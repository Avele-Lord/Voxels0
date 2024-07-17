// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "Keyboard.h" // need 


bool Keyboard::KeyIsPressed(unsigned char KeyCode) const noexcept
{
	return KeyStates[KeyCode];
}

std::optional<Keyboard::Event> Keyboard::ReadKey() noexcept
{
	if (KeyBuffer.size() > 0u)
	{
		Keyboard::Event e = KeyBuffer.front();
		KeyBuffer.pop();
		return e;
	}
	return {};
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return KeyBuffer.empty();
}

std::optional<char> Keyboard::ReadChar() noexcept
{
	if (CharBuffer.size() > 0u)
	{
		unsigned char Charcode = CharBuffer.front();
		CharBuffer.pop();
		return Charcode;
	}
	return {};
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return CharBuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	KeyBuffer = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept
{
	CharBuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutorepeat() noexcept
{
	AutorepeatEnabled = true;
}

void Keyboard::DisableAutorepeat() noexcept
{
	AutorepeatEnabled = false;
}

bool Keyboard::AutorepeatIsEnabled() const noexcept
{
	return AutorepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char KeyCode) noexcept
{
	KeyStates[KeyCode] = true;
	KeyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, KeyCode));
	TrimBuffer(KeyBuffer);
}

void Keyboard::OnKeyReleased(unsigned char KeyCode) noexcept
{
	KeyStates[KeyCode] = false;
	KeyBuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, KeyCode));
	TrimBuffer(KeyBuffer);
}

void Keyboard::OnChar(char Character) noexcept
{
	CharBuffer.push(Character);
	TrimBuffer(CharBuffer);
}

void Keyboard::ClearState() noexcept
{
	KeyStates.reset();
}

template<typename T>
void Keyboard::TrimBuffer(std::queue<T>& Buffer) noexcept
{
	while (Buffer.size() > BufferSize)
	{
		Buffer.pop();
	}
}