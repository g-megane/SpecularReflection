#pragma once
#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d11_2.h>
#include <wrl\client.h>
#include <memory>
#include "Window.h"

#pragma comment(lib, "d3d11.lib")

namespace Lib
{
    class DirectX11
    {
    public:
        DirectX11(std::shared_ptr<Window> _window);
        ~DirectX11();

        void begineFrame() const;
        void endFrame() const;

    private:
        HRESULT initialize();
        HRESULT createDeviceAndSwapChain();
        HRESULT createRenderTargetView();
        void    setRenderTargetView();

        Microsoft::WRL::ComPtr<ID3D11Device>           device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext>    deviceContext;
        Microsoft::WRL::ComPtr<IDXGISwapChain>         swapChain;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

        D3D_FEATURE_LEVEL featureLevel;
        D3D_DRIVER_TYPE   driverType;

        std::shared_ptr<Window> window;
    };
}
#endif
