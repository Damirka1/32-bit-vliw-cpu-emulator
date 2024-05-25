#pragma once

#include <bitset>
#include <queue>
#include <optional>
#include "MessageHandler.h"
#include "KeyboardEvents.h"

class Keyboard : public MessageHandler
{
	friend class AppWindow;
public:
	Keyboard(unsigned int QueueSize = 20) noexcept;
	bool KeyIsPressed(const unsigned char KeyCode) noexcept;
	std::optional<KeyEvent> GetEvent() noexcept;
	std::optional<char> GetCharacters() noexcept;

private:
	void CALLBACK HandleMsg(HWND& hWnd, UINT& msg, WPARAM& wParam, LPARAM& lParam) noexcept override;
	void PopQueueEv() noexcept;
	void PopQueueCh() noexcept;
	void ClearState() noexcept;

	std::bitset<256> keys;
	std::queue<KeyEvent> Events;
	std::queue<KeyEvent> EventsForWindow;
	std::queue<char> Characters;
	unsigned int QueueSize;
};

