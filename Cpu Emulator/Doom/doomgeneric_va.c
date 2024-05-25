#include "Source/doomkeys.h"

#define DOOMGENERIC_RESX 640 * 2
#define DOOMGENERIC_RESY 400 * 2

#include "Source/doomgeneric.h"

#include "DoomWrapper.h"

void DG_Init()
{
	
}

void DG_DrawFrame()
{
	DrawFrame(DG_ScreenBuffer);
}


void DG_SleepMs(uint32_t ms)
{
	SleepMs(ms);
}

uint32_t DG_GetTicksMs()
{
	return GetTicksMs();
}


int DG_GetKey(int* pressed, unsigned char* doomKey)
{
	return GetKey(pressed, doomKey);
}


void DG_SetWindowTitle(const char* title)
{
	SetWindowTitle(title);
}