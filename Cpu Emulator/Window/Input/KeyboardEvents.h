#pragma once

class KeyEvent
{
public:
	enum class Type
	{
		Pressed,
		Released,
		Undefined
	};

	KeyEvent() noexcept;
	KeyEvent(unsigned char Code, Type type) noexcept;

	bool operator==(const char Key)  noexcept;

	unsigned char GetCode() noexcept;

	Type GetType() noexcept;

private:
	unsigned char Code;
	Type t;
};
