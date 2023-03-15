#include <windows.h>
#include <opencv2/opencv.hpp>

void screenshotBackgroundHiddenWindowWindowsGraphicsCapture()
{
	// HWND hwnd = FindWindowA(NULL, "Dofus Retro");
	HWND hwnd = FindWindowA(NULL, "Douwi - Dofus Retro v1.39.8");
	if (hwnd == NULL)
		std::cout << "hwnd error" << std::endl;

	HDC hdcScreen = GetDC(hwnd);
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	HDC hdcMemory = CreateCompatibleDC(hdcScreen);
	HBITMAP hbmScreen = CreateCompatibleBitmap(hdcScreen, width, height);
	SelectObject(hdcMemory, hbmScreen);
	BitBlt(hdcMemory, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);
	ReleaseDC(hwnd, hdcScreen);
	BITMAPINFOHEADER bi;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	cv::Mat img(height, width, CV_8UC4);
	GetDIBits(hdcMemory, hbmScreen, 0, height, img.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
	cv::imshow("test", img);
	cv::waitKey(0);
	DeleteObject(hbmScreen);
	DeleteDC(hdcMemory);
}

int main()
{
	screenshotBackgroundHiddenWindow();
	std::cout << "END OF CODE" << std::endl;
	return 0;
}