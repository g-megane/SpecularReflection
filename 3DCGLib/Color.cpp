#include "Color.h"

namespace Lib
{
    // コンストラクタ
    Color::Color(const float _r, const float _g, const float _b, const float _a)
        : r(_r), g(_g), b(_b), a(_a)
    {
    }
    // コピーコンストラクタ
    Color::Color(const Color &other) : r(other.r), g(other.g), b(other.b), a(other.a)
    {
    }
    // デストラクタ
    Color::~Color()
    {
    }

    const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::BLACK(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::RED(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::BLUE(0.0f, 0.0f, 1.0f, 1.0f);
}