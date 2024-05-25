#pragma once
#include <Windows.h>

class MessageHandler
{
	friend class AppWindow;
protected:
	MessageHandler() = default;
	MessageHandler(MessageHandler&) = delete;
	virtual void CALLBACK HandleMsg(HWND& hWnd, UINT& msg, WPARAM& wParam, LPARAM& lParam) noexcept = 0;
	//virtual ~MessageHandler() = default;
};