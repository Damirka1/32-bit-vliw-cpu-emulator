#include "Terminal.h"

#include "../AppWindow.h"

Terminal::Terminal(AppWindow* window, Graphics* gfx, int pos_x, int pos_y, int width, int height)
    :
    WindowElement(pos_x, pos_y, width, height)
{
    // Initialize DirectWrite
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));

    // Create text format
    pDWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
        24, L"", &pTextFormat);

    // Set text alignment
    pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    layoutRect = D2D1::RectF(pos_x, pos_y, width, height);

    gfx->GetRenderTarget()->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &pBrush
    );

    window->SetTimerForWindow(1, 500);

    commands = {
        {L"/clear", [=]() { InputText.clear(); CursorPositionX = 0; CursorPositionY = 0; }},
        {L"/hello", [=]() { InputText += L"Hello, World!\n"; CursorPositionX = 0; ++CursorPositionY; }},
        {L"/undef", [=]() { InputText += L"Command unknown!\n"; CursorPositionX = 0; ++CursorPositionY; }},
    };
}

void Terminal::Render(Graphics* gfx)
{
    auto* pRT = gfx->GetRenderTarget();

    pRT->DrawTextW(InputText.c_str(), InputText.length(), pTextFormat, &layoutRect, pColor);

    /*if (!inputText.empty())
    {
        std::wstring textBeforeCursor = inputText.substr(0, cursorPositionX);
        DWRITE_TEXT_METRICS metrics;
        IDWriteTextLayout* pTextLayout = nullptr;

        pDWriteFactory->CreateTextLayout(
            textBeforeCursor.c_str(),
            static_cast<UINT32>(textBeforeCursor.length()),
            pTextFormat,
            width,
            height,
            &pTextLayout
        );

        pTextLayout->GetMetrics(&metrics);

        float cursorX = 0;        

        float cursorY = (metrics.lineCount) * (metrics.height / metrics.lineCount);

        if (textBeforeCursor.back() != L'\n')
            cursorX = metrics.widthIncludingTrailingWhitespace;

        pRT->DrawLine(
            D2D1::Point2F(cursorX, cursorY),
            D2D1::Point2F(cursorX, cursorY - 24),
            pBrush,
            2.0f
        );

        pTextLayout->Release();
    }
    else
    {


    }*/
    if (CursorVisible)
    {
        pRT->DrawLine(
            D2D1::Point2F(CursorPositionX * 13.1953125, CursorPositionY * 28.1015625),
            D2D1::Point2F(CursorPositionX * 13.1953125, CursorPositionY * 28.1015625 + 24),
            pBrush,
            2.0f
        );
    }
}

void Terminal::HandleChar(char ch)
{
    size_t currentLineStart = InputText.rfind(L'\n');

    if (ch == VK_BACK && CursorPositionX > 0)
    {
        if (InputText.size() > 0)
        {
            std::wstring ch;
            if (currentLineStart == (size_t)-1)
            {
                ch = InputText.erase(CursorPositionX - 1, 1);
                --CursorPositionX;
            }
            else
            {
                ch = InputText.erase(currentLineStart + 1 + CursorPositionX - 1, 1);
                --CursorPositionX;
            }

            //if (CursorPositionX == 0 || ch[0] == L'\n')
            //{
            //    // Remove \n
            //    if (InputText.size() > 0)
            //    {
            //        ch = InputText.erase(InputText.length() - 1, 1);
            //        --CursorPositionY;
            //        /*size_t st = inputText.find_last_of(L'\n');
            //        size_t l = inputText.length() - st;*/

            //        size_t newCurrentLineStart = InputText.rfind(L'\n');

            //        CursorPositionX = currentLineStart - newCurrentLineStart - 1;
            //    }
            //    
            //}
        }
    }
    else if (ch == VK_BACK)
        return;
    else if (ch == VK_RETURN)
    {
        std::wstring currentLine;
        size_t lastNewLine = InputText.rfind(L'\n');
        if (lastNewLine == std::wstring::npos)
            currentLine = InputText.substr(0, CursorPositionX);
        else
            currentLine = InputText.substr(lastNewLine + 1, CursorPositionX - lastNewLine - 1);

        InputText += L'\n';
        CursorPositionX = 0;
        ++CursorPositionY;

        if(commands.find(currentLine) == commands.end()) 
        {
            commands[L"/undef"]();
        }
        else 
        {
            commands[currentLine]();
        }   
    }
    else
    {
        if (currentLineStart == (size_t)-1)
        {
            InputText.insert(CursorPositionX, 1, ch);
            ++CursorPositionX;
        }
        else 
        {
            size_t st_prev = InputText.find_last_not_of(L'\n');
            size_t st = InputText.find_last_of(L'\n');
            //size_t l = st_prev - st;
            size_t l = currentLineStart + CursorPositionX;
            InputText.insert(currentLineStart + 1 + CursorPositionX, 1, ch);
            ++CursorPositionX;
        }
    }
}

void Terminal::HandleKeyCode(unsigned char code)
{
    if (code == VK_LEFT)
        UpdateCursor(-1);
    else if (code == VK_RIGHT)
        UpdateCursor(1);
}

void Terminal::UpdateCursor(int direction)
{
    if (direction < 0 && CursorPositionX > 0)
    {
        --CursorPositionX;
    }
    else if (direction > 0 && CursorPositionX < InputText.length())
    {
        ++CursorPositionX;
    }
}

void Terminal::HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_KEYDOWN:
        break;
    case WM_LBUTTONDOWN:
        break;
    case WM_MOUSEMOVE:
        POINTS p = MAKEPOINTS(lParam);

        if ((p.x >= x && p.x <= x + width))
        {
            Hover = true;
            OnMouseEnterListener();
        }
        else
        {
            Hover = false;
            OnMouseExitListener();
        }

        break;

    case WM_TIMER:
        CursorVisible = !CursorVisible;
        break;
    }
}
