#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#ifndef STRICT
#define STRICT
#endif
#define WIN32_LEAN_AND_MEAN
/*
STRICT
    ・厳密な型チェックがおこなわれるようになる
WIN32_LEAN_AND_MEAN
    ・必要最低限のヘッダのみインクルード
    ・コンパイル時間の短縮
*/

#include <Windows.h>

namespace Lib
{
    class Window
    {
    public:
        Window(const LPCWSTR _windowName, const LONG _windowWidth, const LONG _windowHeight);
        ~Window();

        MSG Update();
        HWND getHWND() const;
        RECT getWindowRect() const;

    private:
        HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
        static LRESULT CALLBACK WndProck(HWND _hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        int Initialize();

        LPCWSTR windowName;
        HWND hWnd;
        RECT windowRect;
    };
}
#endif