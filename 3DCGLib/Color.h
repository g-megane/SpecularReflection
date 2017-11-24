#pragma once
#ifndef COLOR_H
#define COLOR_H

namespace Lib
{
    class Color
    {
    public:
#pragma warning(disable:4201)
        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            }; 
            float rgba[4];
        };
#pragma warning(default:4201)

        // コンストラクタ
        Color(const float _r = 1.0f, const float _g = 1.0f, const float _b = 1.0f, const float _a = 1.0f);

        // コピーコンストラクタ
        Color(const Color &other);

        // デストラクタ
        ~Color();

        // 演算子オーバーロード
        Color operator+(const Color& other) const
        {
            return Color(r + other.r, g + other.g, b + other.b, a + other.a);
        }
        Color operator-(const Color& other) const
        {
            return Color(r - other.r, g - other.g, b - other.b, a - other.a);
        }
        Color &operator=(const Color& other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;

            return *this;
        }
        Color& operator+=(const Color& other)
        {
            return *this = *this + other;
        }
        Color& operator-=(const Color& other)
        {
            return *this = *this - other;
        }
        bool operator==(const Color& other) const
        {
            return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
        }
        bool operator!=(const Color& other) const
        {
            return !(*this == other);
        }

        static const Color WHITE;
        static const Color BLACK;
        static const Color RED;
        static const Color GREEN;
        static const Color BLUE;
    };
}

#endif
