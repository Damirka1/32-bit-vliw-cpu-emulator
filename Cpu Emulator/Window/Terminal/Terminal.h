#pragma once
#include <string>
#include "../Direct2D/Graphics.h"
#include "../WindowElements/WindowElements.h"

#include <map>
#include <functional>

class Graphics;
class AppWindow;

class Terminal : public WindowElement
{
public:
    Terminal(AppWindow* window, Graphics* gfx, int pos_x, int pos_y, int width, int height);

    void Render(Graphics* gfx) override;
    
    void HandleChar(char ch);
    void HandleKeyCode(unsigned char code);

    void AddCommand(std::wstring cmd, std::function<void()> function)
    {
        commands[cmd] = function;
    }

    void Print(std::wstring str)
    {
        InputText += str;
        if (str.rfind('\n') != -1)
        {
            CursorPositionX = 0;
            ++CursorPositionY;
        }
        else
            CursorPositionX += str.length();
    }

private:
    void UpdateCursor(int direction);

    void HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) override;
	

private:
    std::wstring InputText = L"";
    size_t CursorPositionX = 0;
    size_t CursorPositionY = 0;
    bool CursorVisible = false;

    IDWriteFactory* pDWriteFactory = NULL;
    IDWriteTextFormat* pTextFormat = NULL;
    ID2D1SolidColorBrush* pBrush = nullptr;
    D2D1_RECT_F layoutRect;

    std::map<std::wstring, std::function<void()>> commands;
};

