#pragma once
#include "WindowElements.h"
#include "Button.h"

class Graphics;

class CloseButton : public Button
{
public:
	CloseButton(int wWidth, int wHeight, Graphics* gfx)
		:
		Button(wWidth, 10, 10, 10)
	{
		// Create close button
		SetColor(RGB(242, 108, 79), gfx);
		SetHoverColor(RGB(255, 255, 255), gfx);
	}

	void Render(Graphics* gfx) override
	{
		auto* pRT = gfx->GetRenderTarget();

			pRT->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x - width), static_cast<FLOAT>(y / 2)),
			D2D1::Point2F(static_cast<FLOAT>(x + width / 2), static_cast<FLOAT>(y + height)),
			Hover ? pHoverColor : pColor,
			2
		);

		pRT->DrawLine(
			D2D1::Point2F(static_cast<FLOAT>(x + width / 2), static_cast<FLOAT>(y / 2)),
			D2D1::Point2F(static_cast<FLOAT>(x - width), static_cast<FLOAT>(y + height)),
			Hover ? pHoverColor : pColor,
			2
		);
	}
};

class UpButton : public Button
{
	UpButton(int wWidth, int wHeight, Graphics* gfx)
		:
		Button(wWidth, 10, 10, 10)
	{
		// Create close button
		SetColor(RGB(200, 200, 200), gfx);
		SetHoverColor(RGB(255, 255, 255), gfx);
	}
};

class DownButton : public Button
{
	DownButton(int wWidth, int wHeight, Graphics* gfx)
		:
		Button(wWidth, 10, 10, 10)
	{
		// Create close button
		SetColor(RGB(200, 200, 200), gfx);
		SetHoverColor(RGB(255, 255, 255), gfx);
	}
};
