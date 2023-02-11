#pragma comment(lib,"gdiplus.lib")
#pragma comment(linker, "/opt:nowin98")
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
CHAR szClassName[]="window";

void paint(HDC hdc)
{
	Graphics g(hdc);
	Image image(L"sample.jpg");
	g.DrawImage(&image,0,0,image.GetWidth(),image.GetHeight());
	return;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (msg){
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		paint(hdc);
		EndPaint(hWnd,&ps);
		break;		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	ULONG_PTR gdiToken;
	GdiplusStartupInput gdiSI;
	GdiplusStartup(&gdiToken,&gdiSI,NULL);
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"ƒ^ƒCƒgƒ‹",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiToken);
	return (msg.wParam);
}
