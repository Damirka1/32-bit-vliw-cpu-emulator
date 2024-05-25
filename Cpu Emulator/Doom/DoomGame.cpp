#include "DoomGame.h"

#include "../Window/AppWindow.h"
extern "C" {
#include "Source/doomgeneric.h"
#include "Source/doomkeys.h"
}

#define KEYQUEUE_SIZE 16

static unsigned short s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(unsigned char key)
{
	switch (key)
	{
	case VK_RETURN:
		key = KEY_ENTER;
		break;
	case VK_ESCAPE:
		key = KEY_ESCAPE;
		break;
	case 'a':
		key = KEY_LEFTARROW;
		break;
	case 'd':
		key = KEY_RIGHTARROW;
		break;
	case 'w':
		key = KEY_UPARROW;
		break;
	case 's':
		key = KEY_DOWNARROW;
		break;
	case VK_CONTROL:
		key = KEY_FIRE;
		break;
	case VK_SPACE:
		key = KEY_USE;
		break;
	case VK_SHIFT:
		key = KEY_RSHIFT;
		break;
	default:
		key = tolower(key);
		break;
	}

	return key;
}

static unsigned char DoomKeyconvertToKey(unsigned char* key)
{
	unsigned char rKey;
	switch (*key)
	{
	case KEY_ENTER:
		rKey = VK_RETURN;
		break;
	case KEY_ESCAPE:
		rKey = VK_ESCAPE;
		break;
	case KEY_LEFTARROW:
		rKey = 'a';
		break;
	case KEY_RIGHTARROW:
		rKey = 'd';
		break;
	case KEY_UPARROW:
		rKey = 'w';
		break;
	case KEY_DOWNARROW:
		rKey = 's';
		break;
	case KEY_FIRE:
		rKey = VK_CONTROL;
		break;
	case KEY_USE:
		rKey = VK_SPACE;
		break;
	case KEY_RSHIFT:
		rKey = VK_SHIFT;
		break;
	default:
		rKey = tolower(*key);
		break;
	}

	return rKey;
}

void DoomGame::AddKeyToQueue(int pressed, unsigned char keyCode)
{
	unsigned char key = convertToDoomKey(keyCode);

	unsigned short keyData = (pressed << 8) | key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

DoomGame::DoomGame(int w, int h, AppWindow* window, Graphics* gfx, char** argv, int argc)
	:
	w(w),
	h(h),
	argv(argv),
	argc(argc),
	pWindow(window),
	pGraphics(gfx)
{
}
void DoomGame::Run()
{
	pWindow->AddMessageHandler("DoomKeyboard", &kb);
	doomgeneric_Create(argc, argv);
}

static DoomGame* INSTANCE;

DoomGame* DoomGame::CreateInstance(int w, int h, AppWindow* window, Graphics* gfx, char** argv, int argc)
{
	if (INSTANCE == nullptr)
		INSTANCE = new DoomGame(w, h, window, gfx, argv, argc);
	return INSTANCE;
}

DoomGame* DoomGame::GetInstance()
{
	return INSTANCE;
}

void DoomGame::Tick()
{
	doomgeneric_Tick();
}


void DoomGame::SetWindowTitle(const char* title)
{
	pWindow->SetTitle(title);
}


int DoomGame::GetKey(int* pressed, unsigned char* doomKey)
{
	if (kb.s_KeyQueueReadIndex == kb.s_KeyQueueWriteIndex)
	{
		//key queue is empty

		return 0;
	}
	else
	{
		unsigned short keyData = kb.s_KeyQueue[kb.s_KeyQueueReadIndex];
		
		kb.s_KeyQueue[kb.s_KeyQueueReadIndex] = 0;

		kb.s_KeyQueueReadIndex++;
		kb.s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

		*pressed = keyData >> 8;
		*doomKey = keyData & 0xFF;

		return 1;
	}
}


unsigned long long DoomGame::GetTicksMs()
{
	return GetTickCount64();
}


void DoomGame::SleepMs(unsigned int ms)
{
	Sleep(ms);
}

void DoomGame::DrawFrame(void* buffer)
{
	if(!pBitmap)
	{
		D2D1_SIZE_U size = D2D1::SizeU(w, h);

		D2D1_BITMAP_PROPERTIES bitmapProperties = D2D1::BitmapProperties(
			D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));

		pGraphics->GetRenderTarget()->CreateBitmap(size, bitmapProperties, &pBitmap);
	}

	D2D1_RECT_U rect = D2D1::RectU(0, 0, w, h);
	pBitmap->CopyFromMemory(&rect, buffer, w * 4);

	pGraphics->GetRenderTarget()->BeginDraw();
	pGraphics->GetRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::White));

	pGraphics->GetRenderTarget()->DrawBitmap(
		pBitmap,
		D2D1::RectF(0, 0, static_cast<float>(w), static_cast<float>(h)));

	pGraphics->GetRenderTarget()->EndDraw();	
}
