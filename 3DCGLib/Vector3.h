#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H
#include <cmath>
#include <cfloat>

namespace Lib
{
    class Vector3
    {
    public:
        float x;
        float y;
        float z;

        // デフォルトコンストラクタ
        Vector3();

        // コピーコンストラクタ
        Vector3(const Vector3 &other);

        // デストラクタ
        ~Vector3();

        // コンストラクタ
        Vector3(const float _x, const float _y, const float _z);

        // 指定座標に移動
        void move(const float _x, const float _y, const float _z);
        void move(const Vector3 &other);

        // 座標を引数分ずらす
        void translate(const float _x, const float _y, const float _z);
        void translate(const Vector3 &vec);

        // 内積を求める
        float dot(const Vector3 &other) const;
        
        // 外積を求める
        Vector3 cross(const Vector3 &other) const;

        // 長さを求める
        float length() const;

        // 距離を求める
        float distance(const Vector3 &other) const;

        // 正規化する
        Vector3 normalize() const;

        // 演算子オーバーロード
        Vector3 & operator+=(const Vector3 &other)
        {
            return *this = *this + other;
        }
        Vector3 & operator-=(const Vector3 &other)
        {
            return *this = *this - other;
        }
        Vector3 & operator*=(const float scalar)
        {
            return *this = *this / scalar;
        }
        Vector3 & operator/=(const float scalar)
        {
            return *this = *this / scalar;
        }
        const Vector3 operator+(const Vector3 &other) const
        {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }
        const Vector3 operator-(const Vector3 &other) const
        {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        const Vector3 operator*(const float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
        const Vector3 operator/(const float scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }
        const Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }
        bool operator==(const Vector3 &other) const
        {
            return (x == other.x) && (y == other.y) && (z == other.z);
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

        // 定数
        static const Vector3 ZERO;
        static const Vector3 UP;
        static const Vector3 DOWN;
        static const Vector3 LEFT;
        static const Vector3 RIGHT;
        static const Vector3 FORWARD;
        static const Vector3 BACK;
    };

}


#endif