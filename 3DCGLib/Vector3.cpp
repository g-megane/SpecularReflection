#include "Vector3.h"

namespace Lib
{
    // デフォルトコンストラクタ
    Vector3::Vector3()
    {
        *this = Vector3::ZERO;
    }

    // コピーコンストラクタ
    Vector3::Vector3(const Vector3 &other)
    {
        *this = other;
    }

    // デストラクタ
    Vector3::~Vector3()
    {
    }
    // コンストラクタ
    Vector3::Vector3(
        const float _x,
        const float _y,
        const float _z
    )
    {
        x = _x;
        y = _y;
        z = _z;
    }

    // 指定座標に移動
    void Vector3::move(const float _x, const float _y, const float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    void Vector3::move(const Vector3 &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    // 座標を引数分ずらす
    void Vector3::translate(const float _x, const float _y, const float _z)
    {
        x += _x;
        y += _y;
        z += _z;
    }
    void Vector3::translate(const Vector3 &vec)
    {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }
    // 内積を求める
    float Vector3::dot(const Vector3 &other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }
    // 外積を求める
    Vector3 Vector3::cross(const Vector3 &other) const
    {
        return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }
    // 長さを求める
    float Vector3::length() const
    {
        return std::sqrt(dot(*this));
    }
    // 距離を求める
    float Vector3::distance(const Vector3 &other) const
    {
        return (*this - other).length();
    }
    // 正規化する
    Vector3 Vector3::normalize() const
    {
        const float len = this->length();
        if (len < FLT_EPSILON) {
            return Vector3::ZERO;
        }
        return *this / len;
    }

    const Vector3 Vector3::ZERO   ( 0.0f,  0.0f,  0.0f);
    const Vector3 Vector3::UP     ( 0.0f,  1.0f,  0.0f);
    const Vector3 Vector3::DOWN   ( 0.0f, -1.0f,  0.0f);
    const Vector3 Vector3::LEFT   (-1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::RIGHT  ( 1.0f,  0.0f,  0.0f);
    const Vector3 Vector3::FORWARD( 0.0f,  0.0f,  1.0f);
    const Vector3 Vector3::BACK   ( 0.0f,  0.0f, -1.0f);
}