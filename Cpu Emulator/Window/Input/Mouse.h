#pragma once
#include "MessageHandler.h"
#include "MouseEvents.h"
#include <queue>
#include <optional>
#include <bitset>


class Mouse : public MessageHandler
{
	friend class ScriptManager;
	friend class Window;
	struct RawData
	{
		RawData(LONG dx, LONG dy)
			:
			dx(dx),
			dy(dy)
		{}
		LONG dx, dy;
	};

public:
	Mouse(unsigned int QueueSize = 10, bool UseRawInput = false);
	std::optional<MouseEvent> GetEvent() noexcept;
	std::optional<RawData> GetRawData() noexcept;
	std::pair<short, short> GetPos() noexcept;
	void EnableRawInput() noexcept;
	void DisableRawInput() noexcept;
	bool IsCursorEnabled() noexcept;
	bool IsLbPressed() noexcept;
	bool IsRbPressed() noexcept;
	bool IsMbPressed() noexcept;

private:
	void CALLBACK HandleMsg(HWND& hWnd, UINT& msg, WPARAM& wParam, LPARAM& lParam) noexcept override;
	void PopQueue()  noexcept;
	void PopQueueRawInput() noexcept;


	unsigned int QueueSize;
	bool UseRawInput;
	bool CursorEnabled;
	bool CursorInWindow;
	std::queue<MouseEvent> Events;
	std::queue<MouseEvent> EventsForWindow;
	std::queue<RawData> RawInputEvents;
	std::vector<BYTE> rawBuffer;
	std::pair<short, short> Pos;
	std::bitset<16> Buttons;
	//[Lb, Rb, Mb, ...]
};

