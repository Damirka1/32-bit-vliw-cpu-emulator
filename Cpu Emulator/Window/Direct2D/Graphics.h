#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite_3.h>
#include <wincodec.h>

#include <vector>

class AppWindow;
class WindowElement;

class Graphics
{
public:
	Graphics() = default;
	~Graphics();

	void Initialize(AppWindow* pWindow);

	void Render();

	ID2D1HwndRenderTarget* GetRenderTarget();

	void CreateBitMap(
		UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat,
		UINT cbStride,
		UINT cbBufferSize,
		BYTE* pbBuffer,
		IWICBitmap** ppIBitmap);

private:
	AppWindow* pWindow;

	// Direct2D stuff
	ID2D1Factory* pD2DFactory;
	IDWriteFactory7* pDWFactory;
	ID2D1HwndRenderTarget* pRT; // Render target

	IWICImagingFactory* d2dWICFactory;
	IWICBitmapDecoder* d2dDecoder;
	IWICFormatConverter* d2dConverter;
	IWICBitmapFrameDecode* d2dBmpSrc;
	std::vector<ID2D1Bitmap*> BitMaps;
};