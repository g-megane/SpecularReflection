#pragma once
#ifndef DIRECTX_H
#define DIRECTX_H

#include <d3d11_2.h>
#include <wrl\client.h>
#include <memory>
#include "Window.h"
#include "Matrix.h"

#pragma comment(lib, "d3d11.lib")

namespace Lib
{
    using namespace Microsoft::WRL;

    class DirectX11
    {
    public:
        DirectX11(std::shared_ptr<Window> _window);
        ~DirectX11();

        void begineFrame() const;
        void render();
        void endFrame() const;

    private:
        HRESULT initDevice();
        ComPtr<ID3DBlob> shaderCompile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel);
       
        struct SimpleVertex
        {
            float pos[3];
            float color[4];
        };

        struct ConstantBuffer 
        {
            Matrix<float> world;
            Matrix<float> view;
            Matrix<float> projection;
        };

        ComPtr<ID3D11Device>           device;
        ComPtr<ID3D11DeviceContext>    deviceContext;
        ComPtr<IDXGISwapChain>         swapChain;
        ComPtr<ID3D11RenderTargetView> renderTargetView;
        ComPtr<ID3D11Texture2D>        depthStencil;
        ComPtr<ID3D11DepthStencilView> depthStencilView;
        ComPtr<ID3D11VertexShader>     vertexShader;
        ComPtr<ID3D11PixelShader>      pixelShader;
        ComPtr<ID3D11InputLayout>      vertexLayout;
        ComPtr<ID3D11Buffer>           vertexBuffer;
        ComPtr<ID3D11Buffer>           indexBuffer;
        ComPtr<ID3D11Buffer>           constantBuffer;

        D3D_FEATURE_LEVEL featureLevel;
        D3D_DRIVER_TYPE   driverType;

        Matrix<float> world;
        Matrix<float> view;
        Matrix<float> projection;

        std::shared_ptr<Window> window;
    };
}
#endif
