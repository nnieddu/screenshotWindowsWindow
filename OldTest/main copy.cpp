#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// int main()
// {
//     // Find the window handle of the target window
//     HWND targetWindow = FindWindow(NULL, "Dofus Retro");

//     if (targetWindow == NULL)
//     {
//         cerr << "Failed to find window\n";
//         return 1;
//     }

//     // Get the dimensions of the window
//     RECT windowRect;
//     GetWindowRect(targetWindow, &windowRect);
//     int width = windowRect.right - windowRect.left;
//     int height = windowRect.bottom - windowRect.top;

//     // Get the process ID of the target window
//     DWORD processID;
//     GetWindowThreadProcessId(targetWindow, &processID);

//     // Get a handle to the target process
//     HANDLE processHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, FALSE, processID);

//     if (processHandle == NULL)
//     {
//         cerr << "Failed to get process handle\n";
//         return 1;
//     }

//     // Load the DirectX DLL into the target process
//     HMODULE d3d9Module = LoadLibraryA("d3d9.dll");

//     if (d3d9Module == NULL)
//     {
//         cerr << "Failed to load d3d9.dll\n";
//         return 1;
//     }

//     // Get the addresses of the DirectX functions we need
//     typedef IDirect3D9* (__stdcall* Direct3DCreate9_t)(UINT);
//     typedef HRESULT (__stdcall* Direct3DCreate9Ex_t)(UINT, IDirect3D9Ex**);
//     typedef HRESULT (__stdcall* IDirect3D9Ex_CreateDeviceEx_t)(IDirect3D9Ex*, UINT, D3DPRESENT_PARAMETERS*, D3DDEVICE_CREATION_PARAMETERS*, D3DDISPLAYMODEEX*, IDirect3DDevice9Ex**);
//     Direct3DCreate9_t Direct3DCreate9 = (Direct3DCreate9_t)GetProcAddress(d3d9Module, "Direct3DCreate9");
//     Direct3DCreate9Ex_t Direct3DCreate9Ex = (Direct3DCreate9Ex_t)GetProcAddress(d3d9Module, "Direct3DCreate9Ex");
//     IDirect3D9Ex_CreateDeviceEx_t IDirect3D9Ex_CreateDeviceEx = (IDirect3D9Ex_CreateDeviceEx_t)GetProcAddress(d3d9Module, "IDirect3D9Ex_CreateDeviceEx");

//     if (Direct3DCreate9 == NULL || Direct3DCreate9Ex == NULL || IDirect3D9Ex_CreateDeviceEx == NULL)
//     {
//         cerr << "Failed to get DirectX function addresses\n";
//         return 1;
//     }

//     // Create a IDirect3D9 object in the target process
//     IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);

//     if (d3d == NULL)
//     {
//         cerr << "Failed to create IDirect3D9 object\n";
//         return 1;
//     }

//     // Create a IDirect3D9Ex object in the target process
//     IDirect3D9Ex* d3dEx;
// 		HRESULT result = Direct3DCreate9Ex(D3D_SDK_VERSION, &d3dEx);
// if (result != S_OK)
// {
//     cerr << "Failed to create IDirect3D9Ex object\n";
//     return 1;
// }

// // Create a IDirect3DDevice9Ex object in the target process
// D3DPRESENT_PARAMETERS presentParams = {};
// presentParams.Windowed = TRUE;
// presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
// IDirect3DDevice9Ex* device;
// result = IDirect3D9Ex_CreateDeviceEx(d3dEx, D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, targetWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_FPU_PRESERVE, &presentParams, NULL, &device);

// if (result != S_OK)
// {
//     cerr << "Failed to create IDirect3DDevice9Ex object\n";
//     return 1;
// }

// // Create a texture to hold the screenshot
// IDirect3DTexture9* texture;
// result = device->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &texture, NULL);

// if (result != S_OK)
// {
//     cerr << "Failed to create texture\n";
//     return 1;
// }

// // Get a surface from the texture
// IDirect3DSurface9* surface;
// result = texture->GetSurfaceLevel(0, &surface);

// if (result != S_OK)
// {
//     cerr << "Failed to get surface\n";
//     return 1;
// }

// // Set the render target to the surface
// IDirect3DSurface9* oldRenderTarget;
// result = device->GetRenderTarget(0, &oldRenderTarget);

// if (result != S_OK)
// {
//     cerr << "Failed to get render target\n";
//     return 1;
// }

// result = device->SetRenderTarget(0, surface);

// if (result != S_OK)
// {
//     cerr << "Failed to set render target\n";
//     return 1;
// }

// // Clear the render target
// result = device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

// if (result != S_OK)
// {
//     cerr << "Failed to clear render target\n";
//     return 1;
// }

// // Render the contents of the window to the surface
// result = device->BeginScene();

// if (result != S_OK)
// {
//     cerr << "Failed to begin scene\n";
//     return 1;
// }

// result = device->StretchRect(oldRenderTarget, NULL, surface, NULL, D3DTEXF_NONE);

// if (result != S_OK)
// {
//     cerr << "Failed to stretch rect\n";
//     return 1;
// }

// result = device->EndScene();

// if (result != S_OK)
// {
//     cerr << "Failed to end scene\n";
//     return 1;
// }

// // Save the screenshot as a bitmap file
// IDirect3DSurface9* backBuffer;
// result = device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

// if (result != S_OK)
// {
//     cerr << "Failed to get back buffer\n";
//     return 1;
// }

// // D3DXSaveSurfaceToFile(L"screenshot.bmp", D3DXIFFBMP, backBuffer, NULL, NULL, NULL);
// char filename[256];
// WideCharToMultiByte(CP_ACP, 0, L"screenshot.bmp", -1, filename, 256, NULL, NULL);
// D3DXSaveSurfaceToFile(filename, D3DXIFF_BMP, backBuffer, NULL, NULL);
// // D3DXSaveSurfaceToFile(L"screenshot.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);
// if (result != S_OK)
// {
//     cerr << "Failed to save surface to file\n";
//     return 1;
// }

// // Cleanup
// backBuffer->Release();
// oldRenderTarget->Release();
// surface->Release();
// texture->Release();
// device->Release();
// d3dEx->Release();

// return 0;
// }

// int testTof2(HWND targetWindow, std::string name)

// {
// 	// Find the window handle of the target window

// 	if (targetWindow == NULL)
// 	{
// 		cerr << "Failed to find window\n";
// 		return 1;
// 	}

// 	// Get the dimensions of the window
// 	RECT windowRect;
// 	GetWindowRect(targetWindow, &windowRect);
// 	int width = windowRect.right - windowRect.left;
// 	int height = windowRect.bottom - windowRect.top;

// 	// Create a device context (DC) for the window
// 	HDC windowDC = GetDC(targetWindow);

// 	// Create a memory device context (DC) for the screenshot
// 	HDC memoryDC = CreateCompatibleDC(windowDC);

// 	// Create a bitmap to hold the screenshot
// 	HBITMAP bitmap = CreateCompatibleBitmap(windowDC, width, height);

// 	// Select the bitmap into the memory DC
// 	HGDIOBJ oldBitmap = SelectObject(memoryDC, bitmap);

// 	// Copy the contents of the window's DC to the memory DC
// 	BitBlt(memoryDC, 0, 0, width, height, windowDC, 0, 0, SRCCOPY);

// 	// Save the screenshot as a bitmap file
// 	BITMAP bmp;
// 	GetObject(bitmap, sizeof(bmp), &bmp);
// 	BITMAPFILEHEADER bmfHeader;
// 	bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
// 	bmfHeader.bfSize = bmfHeader.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;
// 	bmfHeader.bfType = 'MB';
// 	BITMAPINFOHEADER bmiHeader;
// 	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
// 	bmiHeader.biWidth = bmp.bmWidth;
// 	bmiHeader.biHeight = -bmp.bmHeight;
// 	bmiHeader.biPlanes = 1;
// 	bmiHeader.biBitCount = 32; // change to 32
// 	bmiHeader.biCompression = BI_RGB;
// 	// bmiHeader.biSizeImage = 15000;
// 	char *pData = new char[bmp.bmWidthBytes * bmp.bmHeight];
// 	GetBitmapBits(bitmap, bmp.bmWidthBytes * bmp.bmHeight, pData);
// 	std::string filename = name + ".bmp";
// 	FILE *fp = fopen(filename.c_str(), "wb");
// 	if (fp != NULL)
// 	{
// 		fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, fp);
// 		fwrite(&bmiHeader, sizeof(BITMAPINFOHEADER), 1, fp);
// 		fwrite(pData, bmp.bmWidthBytes * bmp.bmHeight, 1, fp);
// 		fclose(fp);
// 	}

// 	// Cleanup
// 	delete[] pData;
// 	SelectObject(memoryDC, oldBitmap);
// 	DeleteObject(bitmap);
// 	DeleteDC(memoryDC);
// 	ReleaseDC(targetWindow, windowDC);

// 	return 0;
// }

// // HWND targetWindow = FindWindow(NULL, "Dofus Retro");
// // 	// HWND targetWindow = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");

// // Helper function to get the CLSID of an image encoder based on its MIME type
// int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
// {
// 	UINT num = 0;
// 	UINT size = 0;
// 	GetImageEncodersSize(&num, &size);
// 	if (size == 0)
// 		return -1;
// 	ImageCodecInfo *pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
// 	GetImageEncoders(num, size, pImageCodecInfo);
// 	for (UINT j = 0; j < num; ++j)
// 	{
// 		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
// 		{
// 			*pClsid = pImageCodecInfo[j].Clsid;
// 			free(pImageCodecInfo);
// 			return j;
// 		}
// 	}
// 	free(pImageCodecInfo);
// 	return -1;
// }

// int photoTest(HWND targetWindow, std::string name)
// {
// 	// Initialize GDI+
// 	GdiplusStartupInput gdiplusStartupInput;
// 	ULONG_PTR gdiplusToken;
// 	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

// 	// Find the window handle of the target window

// 	if (targetWindow == NULL)
// 	{
// 		cerr << "Failed to find window\n";
// 		return 1;
// 	}

// 	// Get the dimensions of the window
// 	RECT windowRect;
// 	GetClientRect(targetWindow, &windowRect);
// 	InvalidateRect(targetWindow, &windowRect, TRUE);
// 	UpdateWindow(targetWindow);
// 	GetWindowRect(targetWindow, &windowRect);
// 	int width = windowRect.right - windowRect.left;
// 	int height = windowRect.bottom - windowRect.top;

// 	// Create a device context (DC) for the window
// 	HDC windowDC = GetDC(targetWindow);

// 	// Create a memory device context (DC) for the screenshot
// 	HDC memoryDC = CreateCompatibleDC(windowDC);

// 	// Create a bitmap to hold the screenshot
// 	HBITMAP bitmap = CreateCompatibleBitmap(windowDC, width, height);

// 	// Select the bitmap into the memory DC
// 	HGDIOBJ oldBitmap = SelectObject(memoryDC, bitmap);

// 	// Copy the contents of the window's DC to the memory DC
// 	BitBlt(memoryDC, 0, 0, width, height, windowDC, 0, 0, SRCCOPY);

// 	// Save the screenshot as a bitmap file
// 	Bitmap *bmp = new Bitmap(bitmap, NULL);
// 	CLSID clsid;
// 	GetEncoderClsid(L"image/bmp", &clsid);

// 	std::wstring wsTmp(name.begin(), name.end());

// 	wstring filename = L"screenshot_" + wsTmp + L".bmp";
// 	bmp->Save(filename.c_str(), &clsid, NULL);

// 	// Cleanup
// 	delete bmp;
// 	SelectObject(memoryDC, oldBitmap);
// 	DeleteObject(bitmap);
// 	DeleteDC(memoryDC);
// 	ReleaseDC(targetWindow, windowDC);

// 	// Shutdown GDI+
// 	GdiplusShutdown(gdiplusToken);

// 	return 0;
// }

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	vector<HWND> *pHandles = reinterpret_cast<vector<HWND> *>(lParam);
	pHandles->push_back(hwnd);
	return TRUE;
}

// int gdiPhoto2(HWND targetWindow, std::string name)
// {
// 	// Initialize GDI+
// 	GdiplusStartupInput gdiplusStartupInput;
// 	ULONG_PTR gdiplusToken;
// 	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

// 	// Find the window handle of the target window
// 	if (targetWindow == NULL)
// 	{
// 		cerr << "Failed to find window\n";
// 		return 1;
// 	}

// 	// Get the dimensions of the window
// 	RECT windowRect;
// 	GetWindowRect(targetWindow, &windowRect);
// 	int width = windowRect.right - windowRect.left;
// 	int height = windowRect.bottom - windowRect.top;

// 	// Get the dimensions of the desktop
// 	RECT desktopRect;
// 	HWND desktopWindow = GetDesktopWindow();
// 	GetWindowRect(desktopWindow, &desktopRect);
// 	int desktopWidth = desktopRect.right - desktopRect.left;
// 	int desktopHeight = desktopRect.bottom - desktopRect.top;

// 	// Create a memory device context (DC) for the screenshot
// 	HDC memoryDC = CreateCompatibleDC(NULL);

// 	// Create a bitmap to hold the screenshot of the desktop
// 	HBITMAP desktopBitmap = CreateCompatibleBitmap(GetDC(desktopWindow), desktopWidth, desktopHeight);

// 	// Select the desktop bitmap into the memory DC
// 	HGDIOBJ oldDesktopBitmap = SelectObject(memoryDC, desktopBitmap);

// 	// Capture the contents of the desktop
// 	BitBlt(memoryDC, 0, 0, desktopWidth, desktopHeight, GetDC(desktopWindow), 0, 0, SRCCOPY);

// 	// Create a bitmap to hold the screenshot of the target window
// 	HBITMAP targetBitmap = CreateCompatibleBitmap(memoryDC, width, height);

// 	// Select the target bitmap into the memory DC
// 	HGDIOBJ oldTargetBitmap = SelectObject(memoryDC, targetBitmap);

// 	// Copy the region of the desktop bitmap that corresponds to the target window to the target bitmap
// 	BitBlt(memoryDC, 0, 0, width, height, memoryDC, windowRect.left, windowRect.top, SRCCOPY);

// 	// Save the screenshot as a bitmap file
// 	Bitmap *bmp = new Bitmap(targetBitmap, NULL);
// 	CLSID clsid;
// 	GetEncoderClsid(L"image/bmp", &clsid);
// 	std::wstring wsTmp(name.begin(), name.end());
// 	wstring filename = L"screenshot_" + wsTmp + L".png";
// 	bmp->Save(filename.c_str(), &clsid, NULL);

// 	// Cleanup
// 	delete bmp;
// 	SelectObject(memoryDC, oldTargetBitmap);
// 	DeleteObject(targetBitmap);
// 	SelectObject(memoryDC, oldDesktopBitmap);
// 	DeleteObject(desktopBitmap);
// 	DeleteDC(memoryDC);

// 	// Shutdown GDI+
// 	GdiplusShutdown(gdiplusToken);

// 	return 0;
// }

// int gdiPhoto(HWND targetWindow, std::string name)
// {
// 	// Initialize GDI+
// 	GdiplusStartupInput gdiplusStartupInput;
// 	ULONG_PTR gdiplusToken;
// 	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

// 	if (targetWindow == nullptr)
// 	{
// 		cerr << "Failed to find window\n";
// 		return 1;
// 	}

// 	// Get the dimensions of the window
// 	RECT windowRect;
// 	GetWindowRect(targetWindow, &windowRect);
// 	int width = windowRect.right - windowRect.left;
// 	int height = windowRect.bottom - windowRect.top;

// 	// Create a bitmap to hold the screenshot
// 	Bitmap bitmap(width, height);

// 	// Create a graphics object from the bitmap
// 	Graphics graphics(&bitmap);

// 	// Copy the contents of the window to the bitmap
// 	// graphics.CopyFromScreen(windowRect.left, windowRect.top, 0, 0, Size(width, height));

// 	// Save the screenshot as a PNG file
// 	CLSID pngClsid;
// 	GetEncoderClsid(L"image/png", &pngClsid);
// 	std::wstring wsTmp(name.begin(), name.end());
// 	wstring filename = L"screenshot_" + wsTmp + L".png";
// 	// wchar_t filename[] = L"screenshot.png";
// 	bitmap.Save(filename.c_str(), &pngClsid, nullptr);

// 	// Shutdown GDI+
// 	GdiplusShutdown(gdiplusToken);

// 	return 0;
// }



// int main()
// {
// 	vector<HWND> handles;
// 	EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&handles));
// 	for (auto hwnd : handles)
// 	{
// 		char buffer[256];
// 		GetWindowTextA(hwnd, buffer, sizeof(buffer));
// 		string title(buffer);
// 		if (!title.empty())
// 		{
// 			cout << "Window handle: " << hwnd << " Title: " << title << endl;
// 			// photoTest(hwnd, title);
// 			// testTof2(hwnd, title);
// 			// gdiPhoto(hwnd, title);
// 			gdiPhoto2(hwnd, title);
// 		}
// 	}
// 	return 0;
// }
