#pragma once

#include <bitset>
#include <queue>
#include <optional>
#include "../Window/Input/MessageHandler.h"
#include "../Window/Input/KeyboardEvents.h"

class DoomKeyboard : public MessageHandler
{
	friend class AppWindow;
public:
	DoomKeyboard(unsigned int QueueSize = 20) noexcept;

	void AddKeyToQueue(int pressed, unsigned char keyCode);

private:
	void CALLBACK HandleMsg(HWND& hWnd, UINT& msg, WPARAM& wParam, LPARAM& lParam) noexcept override;

public:
	unsigned short s_KeyQueue[16];
	unsigned int s_KeyQueueWriteIndex = 0;
	unsigned int s_KeyQueueReadIndex = 0;
};

