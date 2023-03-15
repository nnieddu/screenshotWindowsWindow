#define NOMINMAX
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <opencv2/opencv.hpp>
#include <wrl/client.h>

#pragma comment(lib, "d3d11.lib")

using Microsoft::WRL::ComPtr;

int main()
{
	HWND hwnd = FindWindow(NULL, "Dofus Retro");
	// HWND hwnd = FindWindow(NULL, "Douwi - Dofus Retro v1.39.8");
	// HWND hwnd = GetDesktopWindow();

	SetForegroundWindow(hwnd);

	// Initialize Direct3D device and context
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> context;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &device, &featureLevel, &context);
	if (FAILED(hr))
	{
		printf("D3D11CreateDevice failed with error code %d\n", hr);
		return -1;
	}

	RECT rect;
	GetClientRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// Create a texture for storing the screenshot
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	ComPtr<ID3D11Texture2D> texture;
	device->CreateTexture2D(&desc, NULL, &texture);

	// Copy the back buffer to the texture
	ComPtr<IDXGISurface> surface;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;

	ComPtr<IDXGISwapChain> swapChain;
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
																0, nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
																&device, nullptr, &context);

	// ComPtr<ID3D11Texture2D> backBuffer;
	ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
	if (FAILED(hr))
	{
		printf("GetBuffer failed with error code %d\n", hr);
		return -1;
	}

	D3D11_TEXTURE2D_DESC backBufferDesc;
	backBuffer->GetDesc(&backBufferDesc);
	printf("Back buffer format: %d, width: %d, height: %d\n", backBufferDesc.Format, backBufferDesc.Width, backBufferDesc.Height);

	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

	backBuffer.As(&surface);

	context->CopyResource(texture.Get(), backBuffer.Get());
	// context->CopyResource(texture.Get(), surface.Get());
	texture.As(&surface);

	// Lock the texture and get the pixel data
	D3D11_MAPPED_SUBRESOURCE mapped;
	context->Map(texture.Get(), 0, D3D11_MAP_READ, 0, &mapped);
	unsigned char *data = (unsigned char *)mapped.pData;
	int pitch = mapped.RowPitch;

	// Convert the pixel data to OpenCV Mat format
	cv::Mat screenshot(height, width, CV_8UC4, data, pitch);
	cv::imshow("screenshot", screenshot);
	cv::waitKey(0);
	return 0;
}
