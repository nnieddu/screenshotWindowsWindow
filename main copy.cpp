#include <Windows.h>
#include <Windows.Graphics.Capture.h>
#include <Windows.Graphics.DirectX.Direct3D11.Interop.h>
#include <windows.graphics.directx.direct3d11.interop.h>
#include <winrt/base.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <wrl.h>

#include <d3dcommon.h>
#include <d3d11.h>
#include <dxgitype.h>
#include <dxgi1_2.h>
#include <dwmapi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "WindowsApp.lib")

using namespace winrt;
using namespace winrt::Windows::Graphics::Capture;
using namespace winrt::Windows::Graphics::DirectX;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;

int main()
{
    // Initialize the COM apartment state
    winrt::init_apartment();

    // Get the HWND of the window you want to capture
    HWND hwnd = FindWindow(NULL, "My Window");

    // Create a graphics capture item
    GraphicsCaptureItem item = CaptureItemFromWindow(hwnd);

    // Create a graphics capture session
    Direct3D11CaptureFramePool framePool = Direct3D11CaptureFramePool::Create(
        GetDXGIInterfaceFromDevice(d3d11Device.Get()),
        DirectXPixelFormat::B8G8R8A8UIntNormalized,
        1,
        item.Size());
    framePool.StartCapture();

    Direct3D11CaptureSession captureSession = framePool.CreateCaptureSession(item);

    // Start the capture session
    captureSession.StartCapture();

    while (true)
    {
        // Capture the next frame
        Direct3D11CaptureFrame frame = framePool.TryGetNextFrame();

        if (frame != nullptr)
        {
            // Get the texture containing the captured frame
            IDirect3DSurface surface = frame.Surface();
            Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
            winrt::check_hresult(surface.as<IDirect3DDxgiInterfaceAccess>()->GetInterface(__uuidof(ID3D11Texture2D), &texture));

            // Map the texture to read the pixel data
            D3D11_TEXTURE2D_DESC desc;
            texture->GetDesc(&desc);
            D3D11_MAPPED_SUBRESOURCE mappedResource;
            HRESULT hr = d3d11DeviceContext->Map(texture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);
            if (SUCCEEDED(hr))
            {
                // Create a CV::Mat from the pixel data
                cv::Mat screenshot(desc.Height, desc.Width, CV_8UC4, mappedResource.pData, mappedResource.RowPitch);

                // Display the screenshot
                cv::imshow("Screenshot", screenshot);
                cv::waitKey(0);

                // Release resources
                d3d11DeviceContext->Unmap(texture.Get(), 0);

                // Perform any post-processing or analysis here

                // Exit the program
                return 0;
            }
        }
    }
}
