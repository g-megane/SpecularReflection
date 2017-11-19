#include "DirectX11.h"

namespace Lib
{
    // コンストラクタ
    DirectX11::DirectX11(std::shared_ptr<Window> _window)
        :window(_window)
    {
        device           = nullptr;
        deviceContext    = nullptr;
        swapChain        = nullptr;
        renderTargetView = nullptr;
        initialize();
    }

    // デストラクタ
    DirectX11::~DirectX11()
    {
    }

    // フレームの開始
    void DirectX11::begineFrame() const
    {
        float ClearColor[4] { 0.0f, 0.125f, 0.3f, 1.0f };
        deviceContext->ClearRenderTargetView(renderTargetView.Get(), ClearColor);
    }

    // フレームの終了
    void DirectX11::endFrame() const
    {
        swapChain->Present(0, 0);
    }

    // 初期化
    HRESULT DirectX11::initialize()
    {
        auto hr = createDeviceAndSwapChain();
        if (FAILED(hr)) {
            MessageBox(window->getHWND(), L"createDeviceAndSwapChain()の失敗", nullptr, MB_OK);
            return E_FAIL;
        }
        
        hr = createRenderTargetView();
        if (FAILED(hr)) {
            MessageBox(window->getHWND(), L"createRenderTargetView()の失敗", nullptr, MB_OK);
            return E_FAIL;
        }

        setRenderTargetView();

        return S_OK;
    }

    // デバイスレンダーターゲットビューの作成
    HRESULT DirectX11::createDeviceAndSwapChain()
    {
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

        UINT windowWidth  = window->getWindowRect().right  - window->getWindowRect().left;
        UINT windowHeight = window->getWindowRect().bottom - window->getWindowRect().top;

        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 1;								   // スワップチェーンのバッファー数
        sd.BufferDesc.Width =  windowWidth;				   // 解像度の幅
        sd.BufferDesc.Height = windowHeight;			   // 解像度の高さ
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // 表示フォーマット
        sd.BufferDesc.RefreshRate.Numerator = 60;		   // 有理数の最大値
        sd.BufferDesc.RefreshRate.Denominator = 1;		   // 有理数の最小値
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // バックバッファーのサーフェス使用法およびCPUアクセスオプション
        sd.OutputWindow = window->getHWND();			   // 出力ウィンドウへのHWNDハンドル
        sd.SampleDesc.Count = 1;						   // ピクセル単位のマルチサンプリングの数
        sd.SampleDesc.Quality = 0;						   // イメージの品質レベル
        sd.Windowed = TRUE;								   // 出力がウィンドウモードの場合はTRUEそれ以外はFALSE

        HRESULT hr = S_OK;
        for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
        {
            driverType = driverTypes[driverTypeIndex];
            hr = D3D11CreateDeviceAndSwapChain(
                nullptr,                               // 使用するビデオアダプターへのポインター（既定のものを使う場合NULL）
                driverType,                            // 使用するデバイスの種類
                nullptr,                               // ソフトウェアラスタライザーを実装するDLLのハンドル
                0,                                     // 有効にするランタイムレイヤー
                featureLevels,                         // D3D_FEATURE_LEVELの配列へのポインター
                numFeatureLevels,                      // 上記配列の要素数
                D3D11_SDK_VERSION,                     // SDKのバージョン
                &sd,                                   // DXGI_SWAP_CHAINへのポインター
                swapChain.GetAddressOf(),    // IDXGISwapChainオブジェクトへのポインターのアドレスを返す
                device.GetAddressOf(),       // ID3D11Deviceオブジェクトへのポインターのアドレスを返す
                &featureLevel,	                       // D3D_FEATURE_LEVELへのポインターを返す
                deviceContext.GetAddressOf() // ID3D11DeviceContextオブジェクトへのポインターのアドレスを返す
            );

            if (SUCCEEDED(hr)) {
                break;
            }
        }
        if (FAILED(hr)) {
            MessageBox(window->getHWND(), L"D3DCreateDeviceAndSwapChain()の失敗", nullptr, MB_OK);
            return hr;
        }

        return S_OK;
    }

    // レンダーターゲットビューの作成
    HRESULT DirectX11::createRenderTargetView()
    {
        Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

        // バックバッファの取得
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*> (backBuffer.GetAddressOf()));
        // レンダーターゲットビューの作成
        auto hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());
        if (FAILED(hr)) {
            MessageBox(window->getHWND(), L"CreateRenderTargetView()の失敗", nullptr, MB_OK);
            return E_FAIL;
        }

        Microsoft::WRL::ComPtr<IDXGISurface> surf;
        hr = swapChain->GetBuffer(0, IID_PPV_ARGS(surf.GetAddressOf()));
        if (FAILED(hr)) {
            MessageBox(window->getHWND(), L"GetBuffer()の失敗", nullptr, MB_OK);
            return E_FAIL;
        }

        return S_OK;
    }
    
    // レンダーターゲットビューのセット
    void DirectX11::setRenderTargetView()
    {
        deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

        UINT width  = window->getWindowRect().right  - window->getWindowRect().left;
        UINT height = window->getWindowRect().bottom - window->getWindowRect().top;

        // Viewportの初期化
        D3D11_VIEWPORT vp;
        vp.Width    = static_cast<FLOAT>(width);  // ビューポート左側のx位置
        vp.Height   = static_cast<FLOAT>(height); // ビューポート上側のy位置
        vp.MinDepth = 0.0f;                       // ビューポート幅
        vp.MaxDepth = 1.0f;                       // ビューポートの高さ
        vp.TopLeftX =    0;                       // ビューポートの最小深度(0～1)
        vp.TopLeftY =    0;                       // ビューポートの最大深度(0～1)
        deviceContext->RSSetViewports(1, &vp);
    }
}
