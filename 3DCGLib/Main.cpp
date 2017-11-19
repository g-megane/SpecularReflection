#include <Windows.h>
#include "Window.h"
#include "DirectX11.h"

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    std::shared_ptr<Lib::Window> w = std::make_shared<Lib::Window>(L"3DCGLib");

    std::shared_ptr<Lib::DirectX11> directx = std::make_shared<Lib::DirectX11>(w);

    while (w->Update().message != WM_QUIT) {
        directx->begineFrame();

        directx->endFrame();
    }

    return 0;
}