#pragma once
#ifndef MODEL_H
#define MODEL_H
#include "DirectX11.h"
#include "Matrix.h"

namespace Lib
{
    using namespace Microsoft::WRL;

    class Model
    {
    public:
        Model();
        ~Model();

        void render(Matrix &mtWorld, Color &color);

        void setWorldMatrix(Matrix &_world);
        
    private:

        HRESULT init();
        ComPtr<ID3DBlob> shaderCompile(WCHAR* filename, LPCSTR entryPoint, LPCSTR shaderModel);

        struct SimpleVertex
        {
            float pos[3];
            float color[4];
        };

        struct ConstantBuffer
        {
            Matrix world;
            Matrix view;
            Matrix projection;
        };

        ComPtr<ID3D11VertexShader>     vertexShader;
        ComPtr<ID3D11PixelShader>      pixelShader;
        ComPtr<ID3D11InputLayout>      vertexLayout;
        ComPtr<ID3D11Buffer>           vertexBuffer;
        ComPtr<ID3D11Buffer>           indexBuffer;
        ComPtr<ID3D11Buffer>           constantBuffer;

        Matrix world;
    };
}
#endif
