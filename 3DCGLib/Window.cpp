#include "Window.h"

namespace Lib
{
    // コンストラクタ
    Window::Window(const LPCWSTR _windowName)
        :windowName(_windowName)
    {
        Initialize();
    }

    // デストラクタ
    Window::~Window()
    {
    }

    // 初期化
    int Window::Initialize()
    {
        //windowSize = Dimention<int>(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT));
        auto hInstance = GetModuleHandle(nullptr);
        auto nCmdShow = SW_SHOWNORMAL;

        if (FAILED(InitWindow(hInstance, nCmdShow))) {
            OutputDebugString(L"InitWindow()の失敗");
            return 0;
        }

        return 0;
    }
    
    // hWndの取得
    HWND Window::getHWND() const
    {
        return hWnd;
    }

    RECT Window::getWindowRect() const
    {
        return windowRect;
    }
    
    // ウィンドウの初期化
    HRESULT Window::InitWindow(HINSTANCE hInstance, int nCmdShow)
    {
        WNDCLASSEX wcex;
        wcex.cbSize        = sizeof(WNDCLASSEX);						 // 構造体のサイズ
        wcex.style         = CS_HREDRAW | CS_VREDRAW;					 // ウィンドウスタイル
        wcex.lpfnWndProc   = WndProck;							         // ウィンドウプロシージャ
        wcex.cbClsExtra    = 0;									         // ウィンドウクラスに付加したいメモリ
        wcex.cbWndExtra    = 0;									         // ウィンドウに付加したいメモリ
        wcex.hInstance     = hInstance;								     // インスタンスハンドル
        wcex.hIcon         = nullptr;									 // アイコン
        wcex.hCursor       = nullptr;									 // カーソル
        wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1); // 背景色
        wcex.lpszMenuName  = windowName;								 // メニュー
        wcex.lpszClassName = windowName;								 // ウィンドウクラスの名前
        wcex.hIconSm       = nullptr;									 // アイコン小
        if (!RegisterClassEx(&wcex)) {
            OutputDebugString(L"RegisterClassEx()の失敗");
            return E_FAIL;
        }

        // ウィンドウの作成
        windowRect = { 0, 0, static_cast<LONG>(1024), static_cast<LONG>(768) };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
        hWnd = CreateWindow(
            windowName,				// ウィンドウクラス名
            windowName,				// ウィンドウタイトル
            WS_OVERLAPPEDWINDOW,    // ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE,	// ウィンドウスタイル
            CW_USEDEFAULT,			// Y座標の初期値
            CW_USEDEFAULT,			// X座標の初期値
            windowRect.right  - windowRect.left, // 幅の初期値
            windowRect.bottom - windowRect.top, // 高さの初期値
            nullptr,				// 親ウィンドウのハンドル
            nullptr,				// ウィンドウメニュー
            hInstance,				// インスタンスハンドル
            nullptr);				// 作成パラメータ
        if (!hWnd) {
            OutputDebugString(L"CreateWindow()の失敗");
            return E_FAIL;
        }

        // 閉じるボタンの無効化
        // EnableMenuItem(GetSystemMenu(hWnd, NULL), SC_CLOSE, MF_DISABLED);

        ShowWindow(hWnd, nCmdShow);

        return S_OK;
    }
    // ウィンドウプロシージャ
    LRESULT Window::WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC hdc;

        switch (message)
        {
        case WM_PAINT:
            hdc = BeginPaint(_hWnd, &ps);
            EndPaint(_hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            // Escで終了
            if (wParam == VK_ESCAPE) {
                PostQuitMessage(0);
            }
            break;
        default:
            return DefWindowProc(_hWnd, message, wParam, lParam);
        }

        return 0;
    }
    // アップデート
    MSG Window::Update()
    {
        MSG msg = { 0 };


        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return msg;
    }
}