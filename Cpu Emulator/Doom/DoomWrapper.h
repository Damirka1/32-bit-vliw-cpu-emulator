#pragma once

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


EXTERNC void DrawFrame(void* buffer);

EXTERNC void SleepMs(__int32 ms);

EXTERNC __int32 GetTicksMs();

EXTERNC int GetKey(int* pressed, unsigned char* doomKey);

EXTERNC void SetWindowTitle(const char* title);