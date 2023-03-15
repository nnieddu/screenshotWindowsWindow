#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
	HWND targetWindow = FindWindow(NULL, "Dofus Retro");
	// HWND targetWindow = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");
	if (targetWindow == NULL)
	{
		cerr << "Failed to find window\n";
		return 1;
	}
RECT rect;
GetWindowRect(targetWindow, & rect);

HDC hDC = GetDC(targetWindow);
HDC hDCMem = CreateCompatibleDC(hDC);
HBITMAP hBmp = NULL;

hBmp = CreateCompatibleBitmap(hDC, rect.right - rect.left, rect.bottom - rect.top);
    
HGDIOBJ hOld = SelectObject(hDCMem, hBmp);
SendMessage(targetWindow, WM_PRINT, (WPARAM) hDCMem, PRF_CLIENT | PRF_NONCLIENT | PRF_OWNED);
SelectObject(hDCMem, hOld);
    
OpenClipboard(NULL);
EmptyClipboard(); 
SetClipboardData(CF_BITMAP, hBmp);
CloseClipboard();

DeleteDC(hDCMem);
ReleaseDC(targetWindow,hDC);
}