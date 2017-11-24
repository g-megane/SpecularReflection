#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include "Vector3.h"

namespace Lib
{
    class Matrix
    {
    public:
// unionの警告を消すため
#pragma warning(disable:4201)
        union
        {
            struct
            {
                float m11; float m12; float m13; float m14;
                float m21; float m22; float m23; float m24;
                float m31; float m32; float m33; float m34;
                float m41; float m42; float m43; float m44;
            };
            float mat4x4[4][4];
            float mat16[16];
        };
#pragma warning(default:4201)
        // デフォルトコンストラクタ
        Matrix();
        // コピーコンストラクタ
        Matrix(const Matrix &other);
        // コンストラクタ
        Matrix(
            const float& _m11, const float& _m12, const float& _m13, const float& _m14,
            const float& _m21, const float& _m22, const float& _m23, const float& _m24,
            const float& _m31, const float& _m32, const float& _m33, const float& _m34,
            const float& _m41, const float& _m42, const float& _m43, const float& _m44
        );

        // 平行移動
        static Matrix translate(const Vector3& vec);
        static Matrix translate(const float x, const float y, const float z);

        // x軸回転
        static Matrix rotateX(const float angle);
        // y軸回転
        static Matrix rotateY(const float angle);
        // z軸回転
        static Matrix rotateZ(const float angle);

        // 拡大縮小
        static Matrix scale(const float scale);
        static Matrix scale(const float scaleX, const float scaleY, const float scaleZ);

        // 転置
        static Matrix transpose(const Matrix matrix);

        // 左手座標系ビュー行列の作成
        static Matrix LookAtLH(const Vector3 cameraPos, const Vector3 cameraTarget, const Vector3 cameraUpVec);

        // 左手座標系パースペクティブ射影行列を作成
        static Matrix perspectiveFovLH(float fieldOfViewY, float aspectRatio, float znearPlane, float zfarPlane);

        // 演算子オーバーロード
        Matrix& operator+=(const Matrix& other)
        {
            return *this = *this + other;
        }
        Matrix& operator-=(const Matrix& other)
        {
            return *this = *this - other;
        }
        Matrix& operator*=(const Matrix& other)
        {
            return *this = *this * other;
        }
        Matrix& operator*=(const float scalar)
        {
            return *this = *this * scalar;
        }
        Matrix& operator/=(const Matrix& other)
        {
            return *this = *this / other;
        }
        Matrix operator+(const Matrix& other) const
        {
            return Matrix(
                m11 + other.m11, m12 + other.m12, m13 + other.m13, m14 + other.m14,
                m21 + other.m21, m22 + other.m22, m23 + other.m23, m24 + other.m24,
                m31 + other.m31, m32 + other.m32, m33 + other.m33, m34 + other.m34,
                m41 + other.m41, m42 + other.m42, m43 + other.m43, m44 + other.m44
            );
        }
        Matrix operator-(const Matrix& other) const
        {
            return Matrix(
                m11 - other.m11, m12 - other.m12, m13 - other.m13, m14 - other.m14,
                m21 - other.m21, m22 - other.m22, m23 - other.m23, m24 - other.m24,
                m31 - other.m31, m32 - other.m32, m33 - other.m33, m34 - other.m34,
                m41 - other.m41, m42 - other.m42, m43 - other.m43, m44 - other.m44
            );
        }
        Matrix operator*(const Matrix& other) const
        {
            return Matrix(
                (m11 * other.m11) + (m12 * other.m21) + (m13 * other.m31) + m14 * other.m41,
                (m11 * other.m12) + (m12 * other.m22) + (m13 * other.m32) + m14 * other.m42,
                (m11 * other.m13) + (m12 * other.m23) + (m13 * other.m33) + m14 * other.m43,
                (m11 * other.m14) + (m12 * other.m24) + (m13 * other.m34) + m14 * other.m44,

                (m21 * other.m11) + (m22 * other.m21) + (m23 * other.m31) + m24 * other.m41,
                (m21 * other.m12) + (m22 * other.m22) + (m23 * other.m32) + m24 * other.m42,
                (m21 * other.m13) + (m22 * other.m23) + (m23 * other.m33) + m24 * other.m43,
                (m21 * other.m14) + (m22 * other.m24) + (m23 * other.m34) + m24 * other.m44,

                (m31 * other.m11) + (m32 * other.m21) + (m33 * other.m31) + m34 * other.m41,
                (m31 * other.m12) + (m32 * other.m22) + (m33 * other.m32) + m34 * other.m42,
                (m31 * other.m13) + (m32 * other.m23) + (m33 * other.m33) + m34 * other.m43,
                (m31 * other.m14) + (m32 * other.m24) + (m33 * other.m34) + m34 * other.m44,

                (m41 * other.m11) + (m42 * other.m21) + (m43 * other.m31) + m44 * other.m41,
                (m41 * other.m12) + (m42 * other.m22) + (m43 * other.m32) + m44 * other.m42,
                (m41 * other.m13) + (m42 * other.m23) + (m43 * other.m33) + m44 * other.m43,
                (m41 * other.m14) + (m42 * other.m24) + (m43 * other.m34) + m44 * other.m44
            );
        }
        Matrix operator*(const float& scalar) const
        {
            return Matrix(
                m11 * scalar, m12 * scalar, m13 * scalar, m14 * scalar,
                m21 * scalar, m22 * scalar, m23 * scalar, m24 * scalar,
                m31 * scalar, m32 * scalar, m33 * scalar, m34 * scalar,
                m41 * scalar, m42 * scalar, m43 * scalar, m44 * scalar
            );
        }
        Matrix operator/(const Matrix& other) const
        {
            return Matrix(
                (m11 / other.m11) + (m12 / other.m21) + (m13 / other.m31) + m14 / other.m41,
                (m11 / other.m12) + (m12 / other.m22) + (m13 / other.m32) + m14 / other.m42,
                (m11 / other.m13) + (m12 / other.m23) + (m13 / other.m33) + m14 / other.m43,
                (m11 / other.m14) + (m12 / other.m24) + (m13 / other.m34) + m14 / other.m44,

                (m21 / other.m11) + (m22 / other.m21) + (m23 / other.m31) + m24 / other.m41,
                (m21 / other.m12) + (m22 / other.m22) + (m23 / other.m32) + m24 / other.m42,
                (m21 / other.m13) + (m22 / other.m23) + (m23 / other.m33) + m24 / other.m43,
                (m21 / other.m14) + (m22 / other.m24) + (m23 / other.m34) + m24 / other.m44,

                (m31 / other.m11) + (m32 / other.m21) + (m33 / other.m31) + m34 / other.m41,
                (m31 / other.m12) + (m32 / other.m22) + (m33 / other.m32) + m34 / other.m42,
                (m31 / other.m13) + (m32 / other.m23) + (m33 / other.m33) + m34 / other.m43,
                (m31 / other.m14) + (m32 / other.m24) + (m33 / other.m34) + m34 / other.m44,

                (m41 / other.m11) + (m42 / other.m21) + (m43 / other.m31) + m44 / other.m41,
                (m41 / other.m12) + (m42 / other.m22) + (m43 / other.m32) + m44 / other.m42,
                (m41 / other.m13) + (m42 / other.m23) + (m43 / other.m33) + m44 / other.m43,
                (m41 / other.m14) + (m42 / other.m24) + (m43 / other.m34) + m44 / other.m44
            );
        }
        Matrix operator/(const float& scalar) const
        {
            return Matrix(
                m11 / scalar, m12 / scalar, m13 / scalar, m14 / scalar,
                m21 / scalar, m22 / scalar, m23 / scalar, m24 / scalar,
                m31 / scalar, m32 / scalar, m33 / scalar, m34 / scalar,
                m41 / scalar, m42 / scalar, m43 / scalar, m44 / scalar
            );
        }

        static const Matrix Zero;
        static const Matrix Identify;
    };
}

#endif