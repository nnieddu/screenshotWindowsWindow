#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <windows.graphics.capture.interop.h>
#include <holographicspaceinterop.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.Capture.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "WindowsApp.lib")

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Capture;
using namespace Windows::Graphics::DirectX::Direct3D11;
using namespace Windows::Graphics::Imaging;

int main()
{
    init_apartment();

    // Get the window handle
    HWND hWnd = FindWindow(nullptr, "Dofus Retro");
    if (!hWnd)
    {
        std::cout << "Failed to find window." << std::endl;
        return 1;
    }

    // Create the graphics capture item
    auto item = CreateForWindow(hWnd);
    if (!item)
    {
        std::cout << "Failed to create graphics capture item." << std::endl;
        return 1;
    }

    // Create the graphics capture session
    auto session = Direct3D11CaptureFramePool::Create(
        get_activation_factory<Direct3D11CaptureFramePool, IDirect3D11CaptureFramePoolStatics>().Create(
            get_activation_factory<Direct3D11CaptureFramePool>().Get(),
            DirectXPixelFormat::B8G8R8A8UIntNormalized,
            2,
            item.Size()
        ),
        item.GraphicsDevice()
    ).CreateCaptureSession(item);

    // Start the capture session
    session.StartCapture();

    // Capture a frame
    auto frame = session.TryGetNextFrame();
    if (!frame)
    {
        std::cout << "Failed to capture frame." << std::endl;
        session.Close();
        return 1;
    }

    // Convert the frame to a software bitmap
    auto softwareBitmap = SoftwareBitmap::Convert(
        frame.Surface().CreateDrawingSession(nullptr),
        BitmapPixelFormat::Bgra8,
        BitmapAlphaMode::Premultiplied
    );

    // Create a file name for the screenshot
    std::wostringstream fileNameStream;
    fileNameStream << L"screenshot_" << GetTickCount64() << L".png";
    auto fileName = fileNameStream.str();

    // Save the software bitmap to a file
    auto stream = InMemoryRandomAccessStream();
    auto encoder = BitmapEncoder::CreateAsync(BitmapEncoder::PngEncoderId(), stream).get();
    encoder.SetSoftwareBitmap(softwareBitmap);
    encoder.FlushAsync().get();
    auto file = StorageFile::CreateStreamedFileFromRandomAccessStreamAsync(
        fileName,
        stream,
        nullptr
    ).get();

    // Release resources
    frame.Close();
    session.Close();

    return 0;
}
