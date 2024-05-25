#include "Graphics.h"

#include "../AppWindow.h"

void Graphics::Initialize(AppWindow* pWindow)
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);

	hr = pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			pWindow->MainWindow,
			D2D1::SizeU(
				pWindow->wWidth,
				pWindow->wHeight)
		),
		&pRT
	);

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWFactory)
	);

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IWICImagingFactory), (void**)(&d2dWICFactory));


	this->pWindow = pWindow;
}

Graphics::~Graphics()
{
	pD2DFactory->Release();
	pRT->Release();

}

void Graphics::Render()
{
	pRT->BeginDraw();
	pRT->Clear(D2D1::ColorF(0.09f, 0.101f, 0.129f, 1.0f));

	for (WindowElement* el : pWindow->WindowElements)
		el->Render(this);


	HRESULT hr = pRT->EndDraw();
}

ID2D1HwndRenderTarget* Graphics::GetRenderTarget()
{
	return pRT;
}

void Graphics::CreateBitMap(UINT uiWidth, UINT uiHeight, REFWICPixelFormatGUID pixelFormat,
	UINT cbStride,
	UINT cbBufferSize,
	BYTE* pbBuffer,
	IWICBitmap** ppIBitmap)
{
	d2dWICFactory->CreateBitmapFromMemory(uiWidth, uiHeight, pixelFormat, cbStride, cbBufferSize, pbBuffer, ppIBitmap);
}

