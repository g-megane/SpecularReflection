#pragma once
#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d11_2.h>
#include <wrl\client.h>
#include <memory>
#include "Singleton.h"
#include "Window.h"
#include "Matrix.h"
#include "Color.h"

#pragma comment(lib, "d3d11.lib")

namespace Lib
{
    using namespace Microsoft::WRL;

    class DirectX11 : public Singleton<DirectX11>
    {
    public:
        ~DirectX11();

        HRESULT initDevice(std::shared_ptr<Window> _window);
        void begineFrame() const;
        void endFrame() const;

        ComPtr<ID3D11Device> getDevice();
        ComPtr<ID3D11DeviceContext> getDeviceContext();

        void    setViewMatrix(const Matrix &_view);
        Matrix &getViewMatrix();
        void    setProjectionMatrix(const Matrix &_projection);
        Matrix &getProjectionMatrix();

    private:
        friend class Singleton<DirectX11>;
        DirectX11();

        ComPtr<ID3D11Device>           device;
        ComPtr<ID3D11DeviceContext>    deviceContext;
        ComPtr<IDXGISwapChain>         swapChain;
        ComPtr<ID3D11RenderTargetView> renderTargetView;
        ComPtr<ID3D11Texture2D>        depthStencil;
        ComPtr<ID3D11DepthStencilView> depthStencilView;

        D3D_FEATURE_LEVEL featureLevel;
        D3D_DRIVER_TYPE   driverType;

        Matrix view;
        Matrix projection;

        std::shared_ptr<Window> window;
    };
}
#endif
