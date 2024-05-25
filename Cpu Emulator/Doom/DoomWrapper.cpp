#include "DoomWrapper.h"

#include "DoomGame.h"

void DrawFrame(void* buffer)
{
	DoomGame::GetInstance()->DrawFrame(buffer);
}

void SleepMs(__int32 ms)
{
	DoomGame::GetInstance()->SleepMs(ms);
}

__int32 GetTicksMs()
{
	return DoomGame::GetInstance()->GetTicksMs();
}

int GetKey(int* pressed, unsigned char* doomKey)
{
	return DoomGame::GetInstance()->GetKey(pressed, doomKey);
}

void SetWindowTitle(const char* title)
{
	DoomGame::GetInstance()->SetWindowTitle(title);
}