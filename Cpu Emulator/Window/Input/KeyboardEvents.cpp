#include "KeyboardEvents.h"

KeyEvent::KeyEvent() noexcept
	:
	Code(0),
	t(Type::Undefined)
{
}

KeyEvent::KeyEvent(unsigned char Code, Type type) noexcept
	:
	Code(Code),
	t(type)
{
}

bool KeyEvent::operator==(const char Key) noexcept
{
	if (t == Type::Pressed && Code == Key)
		return true;
	return false;
}

unsigned char KeyEvent::GetCode() noexcept
{
	return Code;
}

KeyEvent::Type KeyEvent::GetType() noexcept
{
	return t;
}
