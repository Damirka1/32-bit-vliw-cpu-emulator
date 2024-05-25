#include "..\Window\AppWindow.h"
#include "WindowElements/Label.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

LRESULT CALLBACK AppWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		AppWindow* pWnd = static_cast<AppWindow*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&AppWindow::HandleMsgThunk));
		// forward message to window instance handler
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK AppWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window instance
	AppWindow* pWnd = reinterpret_cast<AppWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

void AppWindow::CenterWindow(HWND hWnd)
{
	RECT rc = { 0 };

	GetWindowRect(hWnd, &rc);
	int win_w = rc.right - rc.left;
	int win_h = rc.bottom - rc.top;

	sWidth = GetSystemMetrics(SM_CXSCREEN);
	sHeight = GetSystemMetrics(SM_CYSCREEN);

	wPosX = (sWidth - win_w) / 2;
	wPosY = (sHeight - win_h) / 2;

	SetWindowPos(hWnd, HWND_TOP, wPosX,
		wPosY, 0, 0, SWP_NOSIZE);
}

void AppWindow::UpdateAppWindow(HWND hWnd)
{
	InvalidateRect(hWnd, NULL, TRUE);
}

void AppWindow::CloseAppWindow(HWND hWnd)
{
	Closed = true;
#ifdef _DEBUG
	//DeallocateConsoles();
#endif
	DestroyWindow(hWnd);
	PostQuitMessage(0);
}

void AppWindow::CreateAllWindowElements()
{
	//// Create close button
	//CloseButton.Color = RGB(242, 108, 79);
	//CloseButton.HoverColor = RGB(255, 255, 255);
	//pRT->CreateSolidColorBrush(D2D1::ColorF(0.949f, 0.423f, 0.309f, 1), &CloseButton.pColor);
	//pRT->CreateSolidColorBrush(D2D1::ColorF(1, 1, 1, 1 ), &CloseButton.pHoverColor);
	//CloseButton.width = 10;
	//CloseButton.height = CloseButton.width;
	//CloseButton.x = wWidth - CloseButton.width;
	//CloseButton.y = CloseButton.width;
	//CloseButton.Hover = FALSE;

	//// Create up button
	//UpButton.Color = RGB(200, 200, 200);
	//UpButton.HoverColor = RGB(255, 255, 255);
	//pRT->CreateSolidColorBrush(D2D1::ColorF(0.784f, 0.784f, 0.784f), &UpButton.pColor);
	//UpButton.pHoverColor = CloseButton.pHoverColor;
	//UpButton.width = CloseButton.width - 2;
	//UpButton.height = UpButton.width + 2;
	//UpButton.x = CloseButton.x - (int)(CloseButton.width * 2.5);
	//UpButton.y = UpButton.height;
	//UpButton.Hover = FALSE;

	//// Create down button
	//DownButton.Color = RGB(200, 200, 200);
	//DownButton.HoverColor = RGB(255, 255, 255);
	//DownButton.pColor = UpButton.pColor;
	//DownButton.pHoverColor = UpButton.pHoverColor;
	//DownButton.width = UpButton.width;
	//DownButton.height = 1;
	//DownButton.x = UpButton.x - UpButton.width * 3;
	//DownButton.y = UpButton.y + UpButton.height - DownButton.height;
	//DownButton.Hover = FALSE;

	//// Title label
	//Title.text = L"Discord 2.0";
	//Title.x = 5;
	//Title.y = 5;
	//Title.width = 100;
	//Title.height = 30;
	//pDWFactory->CreateTextFormat(
	//	L"Microsoft Sans Serif", NULL, DWRITE_FONT_WEIGHT_EXTRA_LIGHT,
	//	DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 18.0f, L"", &Title.pFormat
	//);

	//// Child window
	//cPosX = 80;
	//cPosY = 30;
	//cWidth = wWidth;
	//cHeight = wHeight;
	//pRT->CreateSolidColorBrush(D2D1::ColorF(0.137f, 0.149f, 0.180f), &pCBG);

	//HRESULT hr = d2dWICFactory->CreateDecoderFromFilename(L"Resources/Main.jpg", NULL, GENERIC_READ,
	//	WICDecodeMetadataCacheOnLoad, &d2dDecoder);

	//hr = d2dWICFactory->CreateFormatConverter(&d2dConverter);

	//hr = d2dDecoder->GetFrame(0, &d2dBmpSrc);

	//hr = d2dConverter->Initialize(d2dBmpSrc, GUID_WICPixelFormat32bppPBGRA,
	//	WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);

	//ID2D1Bitmap* d2dBmp;

	//hr = pRT->CreateBitmapFromWicBitmap(d2dConverter, NULL, &d2dBmp);

	//BitMaps.push_back(d2dBmp);

	//CloseButton* cs = new CloseButton(wWidth - 10, wHeight, &Graphics);
}

void AppWindow::Initialize()
{
	CenterWindow(MainWindow);

	Graphics.Initialize(this);

	CreateAllWindowElements();
	Initialized = true;
}


LRESULT AppWindow::HandleMsg(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	for (WindowElement* el : WindowElements)
		el->HandleMessages(hWnd, Msg, wParam, lParam);

	// Processing all handlers in map.
	for (auto& el : MessageHandlers)
		el.second->HandleMsg(hWnd, Msg, wParam, lParam);

	switch (Msg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		CloseAppWindow(hWnd);
		break;
	case WM_NCHITTEST:
	{
		LRESULT hit = DefWindowProcW(hWnd, Msg, wParam, lParam);
		if (hit == HTCLIENT)
		{
			POINT p;
			p.x = (short)lParam;
			p.y = (short)(lParam >> 16);
			ScreenToClient(hWnd, &p);

			// Move window
			if (p.y <= 30)
				hit = HTCAPTION;
		}
		return hit;
	}
	default:
		return DefWindowProcW(hWnd, Msg, wParam, lParam);
	}
	return true;
}

AppWindow::AppWindow(HINSTANCE hInstance, int* w, int* h)
{
	CreateAppWindow(hInstance, w, h);
}

BOOL AppWindow::CreateAppWindow(HINSTANCE hInstance, int* w, int* h)
{
#ifdef _DEBUG
	//AllocateConsoles();
#endif

	WNDCLASSEXW WndClass;
	memset(&WndClass, 0, sizeof(WndClass));
	//WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.hInstance = hInstance;
	WndClass.lpszClassName = MainClassName;
	WndClass.cbSize = sizeof(WndClass);
	//WndClass.cbWndExtra = sizeof(LONG_PTR);

	WndClass.hCursor = LoadCursorW(NULL, IDC_ARROW);
	WndClass.lpfnWndProc = AppWindow::HandleMsgSetup;

	RegisterClassExW(&WndClass);

	wWidth, wHeight;

	if (w)
		wWidth = *w;
	else
		wWidth = 800;
	if (h)
		wHeight = *h;
	else
		wHeight = 600;

	MainWindow = CreateWindowExW(
		NULL,
		MainClassName,
		L"32-bit cpu emulator",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, wWidth, wHeight,
		NULL,
		NULL,
		hInstance,
		this);

	if (!MainWindow)
		return FALSE;

	MessageHandlers["kb"] = &kb;
	//MessageHandlers["ms"] = &ms;

	return TRUE;
}

void AppWindow::ShowAppWindow(int nCmdShow)
{
	if (!Initialized)
		Initialize();

	ShowWindow(MainWindow, nCmdShow);
	UpdateWindow(MainWindow);
}

int AppWindow::PeekMsg()
{
	MSG Msg;

	while (PeekMessageW(&Msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}

	if(!GraphicsDisabled)
		Graphics.Render();

	return (int)Msg.wParam;
}

AppWindow::~AppWindow()
{

}
