#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

namespace Lib
{
    template <class T>
    class Vector3
    {
    public:
        // デフォルトコンストラクタ
        Vector3() : x(T()), y(T()), z(T()), w(T())
        {
        }

        // コピーコンストラクタ
        Vector3(const Vector3 &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        // デストラクタ
        ~Vector3()
        {
        }
        // コンストラクタ
        Vector3(
            const T _x = static_cast<T>(0),
            const T _y = static_cast<T>(0),
            const T _z = static_cast<T>(0)
            )
        {
            x = _x;
            y = _y;
            z = _z;
        }

        // 指定座標に移動
        void move(const T _x, const T _y, const T _z = static_cast<T>(0))
        {
            x = _x;
            y = _y;
            z = _z;
        }
        void move(const Vector3 &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }

        // 演算子オーバーロード
        Vector3 & operator+=(const Vector3 &other)
        {
            return *this = *this + other;
        }
        Vector3 & operator-=(const Vector3 &other)
        {
            return *this = *this - other;
        }
        Vector3 & operator*=(const T scalar)
        {
            return *this = *this / other;
        }
        Vector3 & operator/=(const T scalar)
        {
            return *this = *this / other;
        }
        const Vector3 & operator+(const Vector3 &other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        const Vector3 & operator-(const Vector3 &other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        const Vector3 & operator*(const T scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        const Vector3 & operator/(const T scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
        const Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }
        bool operator==(const Vector3 &other) const
        {
            return (x == oher.x) && (y == other.y) && (z == other.z);
        }
        bool operator!=(const Vector3 &other) const
        {
            return !(*this == other);
        }
        bool operator<(const Vector3 &other) const
        {
            if (x < other.x) return true;
            if (y < other.y) return true;
            if (z < other.z) return true;
            return false;
        }

    private:
        T x;
        T y;
        T z;
    };
}

#endif