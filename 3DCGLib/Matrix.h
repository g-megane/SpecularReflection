#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include "Vector3.h"

namespace Lib
{
    template <class T>
    class Matrix
    {
    public:
// unionの警告を消すため
#pragma warning(disable:4201)
        union
        {
            struct
            {
                T m11; T m12; T m13; T m14;
                T m21; T m22; T m23; T m24;
                T m31; T m32; T m33; T m34;
                T m41; T m42; T m43; T m44;
            };
            T mat4x4[4][4];
            T mat16[16];
        };
#pragma warning(default:4201)
        // コピーコンストラクタ
        Matrix(const Matrix &other)
            :m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
             m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
             m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
             m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44)
        {
        }
        // コンストラクタ
        Matrix(
            const T& _m11 = static_cast<T>(1), const T& _m12 = static_cast<T>(0), const T& _m13 = static_cast<T>(0), const T& _m14 = static_cast<T>(0),
            const T& _m21 = static_cast<T>(0), const T& _m22 = static_cast<T>(1), const T& _m23 = static_cast<T>(0), const T& _m24 = static_cast<T>(0),
            const T& _m31 = static_cast<T>(0), const T& _m32 = static_cast<T>(0), const T& _m33 = static_cast<T>(1), const T& _m34 = static_cast<T>(0),
            const T& _m41 = static_cast<T>(0), const T& _m42 = static_cast<T>(0), const T& _m43 = static_cast<T>(0), const T& _m44 = static_cast<T>(1)
        ) :
            m11(_m11), m12(_m12), m13(_m13), m14(_m14),
            m21(_m21), m22(_m22), m23(_m23), m24(_m24),
            m31(_m31), m32(_m32), m33(_m33), m34(_m34),
            m41(_m41), m42(_m42), m43(_m43), m44(_m44)
        {
        }

        // 平行移動
        template<class U>
        static Matrix translate(const Vector3<U>& vec)
        {
            Matrix tmp;
            tmp.m41 = static_cast<T>(vec.x);
            tmp.m42 = static_cast<T>(vec.y);
            tmp.m43 = static_cast<T>(vec.z);
            return tmp;
        }
        template<class U>
        static Matrix translate(const U& x, const U& y, const U& z = static_cast<U>(0))
        {
            Matrix tmp;
            tmp.m41 = static_cast<T>(x);
            tmp.m42 = static_cast<T>(y);
            tmp.m43 = static_cast<T>(z);
            return tmp;
        }
        // 回転
        template<class U>
        static Matrix rotate(const U& angle)
        {
            Matrix tmp;
            tmp.m11 =  std::cos(static_cast<T>(angle));
            tmp.m12 =  std::sin(static_cast<T>(angle));
            tmp.m21 = -std::sin(static_cast<T>(angle));
            tmp.m22 =  std::cos(static_cast<T>(angle));
            return tmp;
        }
        // 拡大縮小
        template<class U>
        static Matrix scale(const U& scale)
        {
            Matrix tmp;
            tmp.m11 = scale;
            tmp.m22 = scale;
            return tmp;
        }
        template<class U>
        static Matrix scale(const U& x, const U& y)
        {
            Matrix tmp;
            tmp.m11 = x;
            tmp.m22 = y;
            return tmp;
        }
        // 転置
        static Matrix transpose(const Matrix matrix)
        {
            return Matrix(
                matrix.m11, matrix.m21, matrix.m31, matrix.m41,
                matrix.m12, matrix.m22, matrix.m32, matrix.m42,
                matrix.m13, matrix.m23, matrix.m33, matrix.m43,
                matrix.m14, matrix.m24, matrix.m34, matrix.m44
            );
        }
        template<class U>
        static Matrix LookAtLH(const Vector3<U> cameraPos, const Vector3<U> cameraTarget, const Vector3<U> cameraUpVec)
        {
            
        }


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
        Matrix& operator*=(const T scalar)
        {
            return *this = *this + scalar;
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
        Matrix operator*(const T& scalar) const
        {
            return Matrix(
                m11 * scalar, m12 * scalar, m13 * scalar, m14 * scalar,
                m21 * scalar, m22 * scalar, m23 * scalar, m24 * scalar,
                m31 * scalar, m32 * scalar, m33 * scalar, m34 * scalar,
                m41 * scalar, m42 * scalar, m43 * scalar, m44 * scalar
            );
        }
        Matrix operator/(const T& scalar) const
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

    template<class T>
    const Matrix<T> Matrix<T>::Zero(
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
    );
    template<class T>
    const Matrix<T> Matrix<T>::Identify(
        static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
    );
}

#endif