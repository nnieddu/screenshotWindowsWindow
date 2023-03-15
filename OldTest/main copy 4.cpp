// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #define _WIN32_WINNT 0x0A00 // define this before including Windows headers
#include <Windows.h>
#include <windef.h>
#include <Shcore.h>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#pragma comment(lib, "user32.lib")

using namespace cv;

int captureTest()
{
	HWND hWnd = FindWindow(NULL, "Dofus Retro v1.39.8");
	Mat image;
	
	if (hWnd == NULL)
		std::cout << "NO HWND FOUND" << std::endl;
	if (hWnd)
	{
		HDC hDC = GetDC(hWnd);

		if (hDC != NULL)
		{
			RECT windowRect;
			GetWindowRect(hWnd, &windowRect);

			int width = windowRect.right - windowRect.left;
			int height = windowRect.bottom - windowRect.top;

			HDC hCaptureDC = CreateCompatibleDC(hDC);
			HBITMAP hBitmap = CreateCompatibleBitmap(hDC, width, height);
			HGDIOBJ hOld = SelectObject(hCaptureDC, hBitmap);

			if (PrintWindow(hWnd, hCaptureDC, 0))
			{
				BITMAPINFO bmi = {0};
				bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				bmi.bmiHeader.biWidth = width;
				bmi.bmiHeader.biHeight = -height;
				bmi.bmiHeader.biPlanes = 1;
				bmi.bmiHeader.biBitCount = 32;
				bmi.bmiHeader.biCompression = BI_RGB;

				BYTE *bits = nullptr;
				HBITMAP hBitmapCopy = CreateDIBSection(hDC, &bmi, DIB_RGB_COLORS, (void **)&bits, nullptr, 0);

				if (hBitmapCopy != nullptr)
				{
					if (GetDIBits(hCaptureDC, hBitmap, 0, height, bits, &bmi, DIB_RGB_COLORS) != 0)
					{
						image.create(height, width, CV_8UC4);
						memcpy(image.data, bits, height * width * 4);
						// cv::cvtColor(image, image, cv::COLOR_RGBA2BGRA);
					}
					cv::imshow("Captured Image", image);
        	cv::waitKey(0);
					DeleteObject(hBitmapCopy);
				}
			}

			SelectObject(hCaptureDC, hOld);
			DeleteObject(hBitmap);
			DeleteDC(hCaptureDC);
			ReleaseDC(hWnd, hDC);
		}
	}

	return 0;
}


// BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
// {
// 	std::vector<HWND> *pHandles = reinterpret_cast<std::vector<HWND> *>(lParam);
// 	pHandles->push_back(hwnd);
// 	return TRUE;
// }

// int main()
// {
// 	// std::vector<HWND> handles;
// 	// EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles));
// 	// for (auto hwnd : handles)
// 	// {
// 	// 	char buffer[256];
// 	// 	GetWindowTextA(hwnd, buffer, sizeof(buffer));
// 	// 	std::string title(buffer);
// 	// 	if (!title.empty())
// 	// 	{
// 	// 		std::cout << "Window handle: " << hwnd << " Title: " << title << std::endl;
// 	// 		// captureTest(hwnd);
// 	// 	}
// 	// }
// 	return 0;
// }










// #define WIN32_LEAN_AND_MEAN
// #define NOMINMAX
// #define _WIN32_WINNT 0x0A00 // define this before including Windows headers
#include <Windows.h>
#include <windef.h>
#include <Shcore.h>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

using namespace cv;

int main()
{
    HWND hWnd = FindWindow(nullptr, "Dofus Retro v1.39.8");
    if (hWnd == nullptr)
    {
        std::cerr << "Could not find window\n";
        return 1;
    }

    RECT rect;
    GetWindowRect(hWnd, &rect);

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HDC hDC = GetDC(hWnd);
    HDC hDCMem = CreateCompatibleDC(hDC);
    HBITMAP hBitmap = CreateCompatibleBitmap(hDC, width, height);

    SelectObject(hDCMem, hBitmap);

    PrintWindow(hWnd, hDCMem, PW_CLIENTONLY);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, bitmap.bmBits);

    DeleteObject(hBitmap);
    DeleteDC(hDCMem);
    ReleaseDC(hWnd, hDC);

    return 0;
}
