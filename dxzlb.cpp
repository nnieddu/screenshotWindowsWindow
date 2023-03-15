#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
	// Find the handle to the target window
	HWND targetWindow = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");

	// Get the dimensions of the target window
	RECT targetRect;
	GetClientRect(targetWindow, &targetRect);

	// Create a Direct3D 9 device for the window
	IDirect3D9 *direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	IDirect3DDevice9 *device;
	direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &device);

	// Create a surface for the window
	IDirect3DSurface9 *surface;
	device->CreateOffscreenPlainSurface(targetRect.right, targetRect.bottom, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &surface, NULL);

	// Copy the contents of the window to the surface
	device->GetFrontBufferData(0, surface);

	// Create an OpenCV Mat object from the surface
	D3DLOCKED_RECT lockedRect;
	surface->LockRect(&lockedRect, NULL, D3DLOCK_READONLY);
	cv::Mat screenshot(targetRect.bottom, targetRect.right, CV_8UC4, lockedRect.pBits, lockedRect.Pitch);
	surface->UnlockRect();

	// Release the Direct3D 9 device and the surface
	device->Release();
	surface->Release();
	direct3D9->Release();

	// Display the screenshot
	std::cout << "Screenshot dimensions: " << screenshot.cols << "x" << screenshot.rows << std::endl;
	if (screenshot.cols > 0 && screenshot.rows > 0)
	{
		try
		{
			// cv::imwrite("screenshot.jpg", screenshot);
			cv::imwrite("screenshot.bmp", screenshot);
			cv::imshow("Screenshot", screenshot);
			cv::waitKey(0);
		}
		catch (cv::Exception &e)
		{
			std::cerr << "OpenCV exception: " << e.what() << std::endl;
		}
	}
	else
	{
		std::cerr << "Failed to capture screenshot" << std::endl;
	}

	return 0;
}
