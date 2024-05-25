#pragma once
#include <utility>

class MouseEvent
{
public:
	enum class Type
	{
		L_Pressed,
		L_Released,
		R_Pressed,
		R_Released,
		WheelDown,
		WheelUp,
		WheelPressed,
		WheelReleased,
		Undefined,
		Move,
		EnterWindow,
		LeaveWindow,
		DoubleClick,
	};

	MouseEvent() noexcept;
	MouseEvent(Type Type, std::pair<short, short> Pos) noexcept;
	bool L_Pressed() noexcept;
	bool R_Pressed() noexcept;
	bool WheelDown() noexcept;
	bool WheelUp() noexcept;
	bool WheelPressed() noexcept;
	std::pair<short, short> GetPos() noexcept;
	bool operator==(Type t) noexcept;

private:
	std::pair<short, short> Pos;
	Type t;
};
