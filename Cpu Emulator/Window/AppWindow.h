#pragma once
#include "Direct2D/Graphics.h"

#include "WindowElements/DefaultElements.h"

#include <vector>
#include <unordered_map>
#include "Input/MessageHandler.h"
#include "Input/Keyboard.h"
//#include "Input/Mouse.h"

class AppWindow
{
	friend class Application;
	friend class Graphics;

public:
	AppWindow() = default;
	AppWindow(HINSTANCE hInstance, int* w, int* h);
	~AppWindow();

	BOOL CreateAppWindow(HINSTANCE hInstance, int* w, int* h);
	void ShowAppWindow(int nCmdShow);
	int PeekMsg();

	void DisableGraphics()
	{
		GraphicsDisabled = true;
	}

	void EnableGraphics()
	{
		GraphicsDisabled = false;
	}

	void SetTitle(const char* title) 
	{
		SetWindowTextA(MainWindow, (LPCSTR) title);
	}

	void AddWindowElement(WindowElement* we) 
	{
		WindowElements.push_back(we);
	}

	void AddMessageHandler(std::string key, MessageHandler* ms)
	{
		MessageHandlers[key] = ms;
	}

	void SetTimerForWindow(int id, int time)
	{
		SetTimer(MainWindow, id, time, nullptr);
	}

	Graphics& GetGraphics() 
	{
		return Graphics;
	}

	Keyboard& GetKeyboard() 
	{
		return this->kb;
	}

	/*const Mouse& GetMouse() 
	{
		return this->ms;
	}*/

	bool IsClosed() 
	{
		return Closed;
	}

private:
	void CenterWindow(HWND hWnd);
	void UpdateAppWindow(HWND hWnd);
	void CloseAppWindow(HWND hWnd);
	void Render();
	void CreateAllWindowElements();
	void Initialize();

	LRESULT CALLBACK HandleMsg(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	LPCWSTR MainClassName = L"MainWindowClass";
	HWND MainWindow;

	Graphics Graphics;

	std::vector<WindowElement*> WindowElements;
	std::unordered_map<std::string, MessageHandler*> MessageHandlers;

	Keyboard kb;
	//Mouse ms;

	int wWidth, wHeight; // Window resolution
	int wPosX, wPosY;  // Window position
	int sWidth, sHeight; // Screen resolution


	BOOL Initialized = false;

	BOOL Closed = false;

	BOOL GraphicsDisabled = false;
};