#pragma once
#include "DoomKeyboard.h"

class AppWindow;
class Graphics;
struct ID2D1Bitmap;

class DoomGame
{
private:
	DoomGame(int w, int h, AppWindow* window, Graphics* gfx, char** argv, int argc);
public:
	static DoomGame* CreateInstance(int w, int h, AppWindow* window, Graphics* gfx, char** argv, int argc);
	
	static DoomGame* GetInstance();

	void Tick();
public:
	void AddKeyToQueue(int pressed, unsigned char keyCode);
	void SetWindowTitle(const char* title);
	int GetKey(int* pressed, unsigned char* doomKey);
	unsigned long long GetTicksMs();
	void SleepMs(unsigned int ms);
	void DrawFrame(void* buffer);
	void Run();

private:
	int w;
	int h;
	char** argv;
	int argc;

	AppWindow* pWindow;
	Graphics* pGraphics;
	DoomKeyboard kb;

	ID2D1Bitmap* pBitmap = nullptr;

};

