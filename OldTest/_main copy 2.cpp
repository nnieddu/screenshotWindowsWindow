#include <windows.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
	// Find the handle to the target window
	HWND targetWindow = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");

	// Get the DPI scaling factor for the window
	HDC windowDC = GetDC(targetWindow);
	int dpiX = GetDpiForWindow(targetWindow);
	ReleaseDC(targetWindow, windowDC);

	// Get the dimensions of the target window, accounting for the DPI scaling factor
	RECT targetRect;
	GetClientRect(targetWindow, &targetRect);
	targetRect.right = MulDiv(targetRect.right, dpiX, 96);
	targetRect.bottom = MulDiv(targetRect.bottom, dpiX, 96);

	// Check if the window is being rendered using hardware acceleration
	HDC targetDC = GetDC(targetWindow);
	bool isHardwareAccelerated = (GetDeviceCaps(targetDC, TECHNOLOGY) == DT_RASDISPLAY);
	ReleaseDC(targetWindow, targetDC);

	if (isHardwareAccelerated) {
		std::cout << "Window is being rendered using hardware acceleration" << std::endl;
		// To disable hardware acceleration, create a manifest file for your application
		// and set the <application> element's 'enableHighDpi' attribute to 'false'
		// For more information, see:
		// https://docs.microsoft.com/en-us/windows/win32/hidpi/disabling-high-dpi-awareness
	}

	// Create a device context for the window
	HDC memDC = CreateCompatibleDC(NULL);
	HBITMAP memBitmap = CreateCompatibleBitmap(memDC, targetRect.right, targetRect.bottom);
	SelectObject(memDC, memBitmap);

	// Copy the contents of the window to the bitmap
	windowDC = GetDC(targetWindow);
	BitBlt(memDC, 0, 0, targetRect.right, targetRect.bottom, windowDC, 0, 0, SRCCOPY);
	ReleaseDC(targetWindow, windowDC);

	// Create an OpenCV Mat object from the bitmap
	cv::Mat screenshot(targetRect.bottom, targetRect.right, CV_8UC4);
	GetBitmapBits(memBitmap, targetRect.right * targetRect.bottom * 4, screenshot.data);

	// Release the device contexts and the bitmap
	DeleteObject(memBitmap);
	DeleteDC(memDC);

	// Check if the screenshot is valid
	if (screenshot.cols > 0 && screenshot.rows > 0)
	{
		// Display the screenshot
		cv::imshow("Screenshot", screenshot);
		cv::waitKey(0);
	}
	else
	{
		std::cerr << "Failed to capture screenshot" << std::endl;
	}

	return 0;
}
