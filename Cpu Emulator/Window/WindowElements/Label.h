#pragma once
#include "WindowElements.h"
#include "../Direct2D/Graphics.h"

class Label : public WindowElement
{
public:
	Label(int pos_x, int pos_y, int width, int height)
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

		layoutRect = D2D1::RectF(pos_x, pos_y, width, height); // Define layout rectangle
	}

	void SetText(const std::wstring& wstr)
	{
		text = wstr.c_str();
	}

	void Render(Graphics* gfx) override
	{
		auto* pRT = gfx->GetRenderTarget();

		if (text)
		{
			pRT->DrawTextW(text, wcslen(text), pTextFormat, &layoutRect, pColor);
		}
	}


private:
	LPCWSTR text = nullptr;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	D2D1_RECT_F layoutRect;
};