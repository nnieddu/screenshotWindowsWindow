#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

int main()
{
    IDirect3DDevice9* g_pd3dDevice;
    IDirect3DSurface9* pSurface = NULL;
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = FALSE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    // d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    // d3dpp.BackBufferFormat = D3DFMT_R8G8B8;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferCount = 1;
    d3dpp.BackBufferWidth = 1280;
    d3dpp.BackBufferHeight = 1024;
    d3dpp.hDeviceWindow = GetDesktopWindow();
    d3dpp.FullScreen_RefreshRateInHz = 0;
    d3dpp.MultiSampleQuality = 0;
    IDirect3D9* direct = Direct3DCreate9(D3D_SDK_VERSION);
    direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetDesktopWindow(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice);

    g_pd3dDevice->CreateOffscreenPlainSurface(1280, 1024, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &pSurface, NULL);
    g_pd3dDevice->GetFrontBufferData(0, pSurface);
    D3DXSaveSurfaceToFile("Desktop.jpg", D3DXIFF_PNG, pSurface, NULL, NULL);
    // D3DXSaveSurfaceToFile("Desktop.jpg", D3DXIFF_JPG, pSurface, NULL, NULL);
    pSurface->Release();

    g_pd3dDevice->Release();
    direct->Release();
    return 0;
}
