#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include <wincodec.h>

#include <string>

class WindowElement
{
	friend class AppWindow;

public:
	WindowElement(int pos_x, int pos_y, int width, int height)
		:
		x(pos_x),
		y(pos_y),
		width(width),
		height(height)
	{
	
	}

	void SetColor(COLORREF color, Graphics* gfx)
	{
		this->Color = color;
		gfx->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f, GetBValue(color) / 255.0f, 1), &pColor);
		
	}

	void SetHoverColor(COLORREF color, Graphics* gfx)
	{
		this->HoverColor = color;
		gfx->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(GetRValue(color) / 255.0f, GetGValue(color) / 255.0f, GetBValue(color) / 255.0f, 1), &pHoverColor);
	}

	virtual void Render(Graphics* gfx)
	{

	}

	virtual void OnClickListener()
	{

	}

	virtual void OnMouseEnterListener()
	{

	}

	virtual void OnMouseExitListener()
	{

	}

	
private:
	virtual void HandleMessages(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_KEYDOWN:
			break;
		case WM_LBUTTONDOWN:
			break;
		case WM_MOUSEMOVE:
			POINTS p = MAKEPOINTS(lParam);
			
			if ((p.x >= x && p.x <= x + width) )
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
		}
		
	}


protected:
	int ElementId;
	std::string ElementName;

	int x, y;
	int width, height;

	BOOL Hover = false;
	COLORREF Color = {0};
	COLORREF HoverColor = {0};

	ID2D1SolidColorBrush* pColor = nullptr;
	ID2D1SolidColorBrush* pHoverColor = nullptr;
};
