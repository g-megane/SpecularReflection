#include <d3dcompiler.h>
#include "DirectX11.h"

#pragma comment(lib, "d3dcompiler.lib")

namespace Lib
{
    // コンストラクタ
    DirectX11::DirectX11()
    {
        device           = nullptr;
        deviceContext    = nullptr;
        swapChain        = nullptr;
        renderTargetView = nullptr;
        depthStencil     = nullptr;
        depthStencilView = nullptr;

    }

    // デストラクタ
    DirectX11::~DirectX11()
    {
    }

    // フレームの開始
    void DirectX11::begineFrame() const
    {
        float ClearColor[4]{ 0.0f, 0.125f, 0.3f, 1.0f };
        deviceContext->ClearRenderTargetView(renderTargetView.Get(), ClearColor);
        // Zバッファーのクリア
        deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    // フレームの終了
    void DirectX11::endFrame() const
    {
        swapChain->Present(0, 0);
    }

    // デバイスの取得
    ComPtr<ID3D11Device> DirectX11::getDevice()
    {
        return device;
    }

    // デバイスコンテキストの取得
    ComPtr<ID3D11DeviceContext> DirectX11::getDeviceContext()
    {
        return deviceContext;
    }

    // ビュー行列を設定
    void DirectX11::setViewMatrix(const Matrix & _view)
    {
        view = _view;
    }

    // ビュー行列を取得
    Matrix & DirectX11::getViewMatrix()
    {
        return view;
    }

    // 射影行列を設定
    void DirectX11::setProjectionMatrix(const Matrix & _projection)
    {
        projection = _projection;
    }

    // 射影行列を取得
    Matrix & DirectX11::getProjectionMatrix()
    {
        return projection;
    }

    // 初期化
    HRESULT DirectX11::initDevice(std::shared_ptr<Window> _window)
    {
        window = _window;
        UINT createDeviceFlags = 0;
#ifdef _DEBUG
        createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        // ドライバーの種類のオプション
        D3D_DRIVER_TYPE driverTypes[] =
        {
            D3D_DRIVER_TYPE_HARDWARE,
            D3D_DRIVER_TYPE_WARP,
            D3D_DRIVER_TYPE_REFERENCE,
        };
        UINT numDriverTypes = ARRAYSIZE(driverTypes);

        // Direct3Dデバイスのターゲットとなる機能セット
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1,
        };
        UINT numFeatureLevels = ARRAYSIZE(featureLevels);

        UINT windowWidth = window->getWindowRect().right - window->getWindowRect().left;
        UINT windowHeight = window->getWindowRect().bottom - window->getWindowRect().top;

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;                                // スワップチェーンのバッファー数
        sd.BufferDesc.Width = windowWidth;                 // 解像度の幅
        sd.BufferDesc.Height = windowHeight;               // 解像度の高さ
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 表示フォーマット
        sd.BufferDesc.RefreshRate.Numerator = 60;          // 有理数の最大値
        sd.BufferDesc.RefreshRate.Denominator = 1;         // 有理数の最小値
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // バックバッファーのサーフェス使用法およびCPUアクセスオプション
        sd.OutputWindow = window->getHWND();               // 出力ウィンドウへのHWNDハンドル
        sd.SampleDesc.Count = 1;                           // ピクセル単位のマルチサンプリングの数
        sd.SampleDesc.Quality = 0;                         // イメージの品質レベル
        sd.Windowed = TRUE;                                // 出力がウィンドウモードの場合はTRUEそれ以外はFALSE

        HRESULT hr = S_OK;
        for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
        {
            driverType = driverTypes[driverTypeIndex];
            hr = D3D11CreateDeviceAndSwapChain(
                nullptr,                               // 使用するビデオアダプターへのポインター（既定のものを使う場合NULL）
                driverType,                            // 使用するデバイスの種類
                nullptr,                               // ソフトウェアラスタライザーを実装するDLLのハンドル
                createDeviceFlags,                     // 有効にするランタイムレイヤー
                featureLevels,                         // D3D_FEATURE_LEVELの配列へのポインター
                numFeatureLevels,                      // 上記配列の要素数
                D3D11_SDK_VERSION,                     // SDKのバージョン
                &sd,                                   // DXGI_SWAP_CHAINへのポインター
                swapChain.GetAddressOf(),              // IDXGISwapChainオブジェクトへのポインターのアドレスを返す
                device.GetAddressOf(),                 // ID3D11Deviceオブジェクトへのポインターのアドレスを返す
                &featureLevel,	                       // D3D_FEATURE_LEVELへのポインターを返す
                deviceContext.GetAddressOf()           // ID3D11DeviceContextオブジェクトへのポインターのアドレスを返す
            );

            if (SUCCEEDED(hr)) {
                break;
            }
        }
        if (FAILED(hr)) {
            MessageBox(nullptr, L"D3DCreateDeviceAndSwapChain()の失敗 : " + hr, L"Error", MB_OK);
            return hr;
        }

        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
        // バックバッファの取得
        hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(backBuffer.GetAddressOf()));
        if (FAILED(hr)) {
            MessageBox(nullptr, L"GetBuffer()の失敗 : " + hr, nullptr, MB_OK);
            return hr;
        }
        // レンダーターゲットビューの作成
        hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());
        if (FAILED(hr)) {
            MessageBox(nullptr, L"CreateRenderTargetView()の失敗 : " + hr, nullptr, MB_OK);
            return hr;
        }

        // ※深度ステンシルはZバッファーとも呼ばれる
        // 深度ステンシル用テクスチャリソースを作成
        D3D11_TEXTURE2D_DESC descDepth;
        ZeroMemory(&descDepth, sizeof(descDepth));
        descDepth.Width = windowWidth;                    // テクスチャーの幅(バックバッファと同じサイズを指定)
        descDepth.Height = windowHeight;                  // テクスチャーの高さ(バックバッファと同じサイズを指定)
        descDepth.MipLevels = 1;                          // ミップマップレベルの最大数
        descDepth.ArraySize = 1;                          // テクスチャー配列内のテクスチャーの数
        descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // テクスチャーのフォーマット
        descDepth.SampleDesc.Count = 1;                   // ピクセル単位のマルチサンプリング数
        descDepth.SampleDesc.Quality = 0;                 // イメージの品質レベル
        descDepth.Usage = D3D11_USAGE_DEFAULT;            // テクスチャーの読み込みおよび書き込み方法を識別する値
        descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;   // パイプラインステージへのバインドに関するフラグ
        descDepth.CPUAccessFlags = 0;                     // 許可するCPUアクセスの種類を指定売るフラグ
        descDepth.MiscFlags = 0;                          // 他の一般性の低いリソースオプションを識別するフラグ
        hr = device->CreateTexture2D(&descDepth, nullptr, depthStencil.GetAddressOf());
        if (FAILED(hr)) {
            MessageBox(nullptr, L"CreateTexture2D()の失敗 : " + hr, L"Error", MB_OK);
            return hr;
        }

        // 深度ステンシルビューからアクセス可能なテクスチャーのサブリソースを指定
        D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
        ZeroMemory(&descDSV, sizeof(descDSV));
        descDSV.Format = descDepth.Format;                     // リソースデータのフォーマット
        descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // リソースのタイプ
        descDSV.Texture2D.MipSlice = 0;                        // 最初に使用するミップマップレベルのインデックス
        // リソースデータへのアクセス用に深度ステンシルビューの作成
        hr = device->CreateDepthStencilView(depthStencil.Get(), &descDSV, depthStencilView.GetAddressOf());
        if (FAILED(hr)) {
            MessageBox(nullptr, L"CreateDepthStencilView()の失敗 : " + hr, L"Error", MB_OK);
            return hr;
        }
        // 深度ステンシルビューをターゲットにセット
        deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), depthStencilView.Get());

        // Viewportの初期化
        D3D11_VIEWPORT vp;
        vp.Width    = static_cast<FLOAT>(windowWidth);  // ビューポート左側のx位置
        vp.Height   = static_cast<FLOAT>(windowHeight); // ビューポート上側のy位置
        vp.MinDepth = 0.0f;                             // ビューポート幅
        vp.MaxDepth = 1.0f;                             // ビューポートの高さ
        vp.TopLeftX = 0;                                // ビューポートの最小深度(0～1)
        vp.TopLeftY = 0;                                // ビューポートの最大深度(0～1)
        deviceContext->RSSetViewports(1, &vp);

        return S_OK;
    }
}
