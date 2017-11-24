#include "Matrix.h"

namespace Lib
{
    Matrix::Matrix()
    {
        *this = Matrix::Zero;
    }
    // コピーコンストラクタ
    Matrix::Matrix(const Matrix &other)
        :m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
         m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
         m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
         m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44)
    {
    }
    // コンストラクタ
    Matrix::Matrix(
        const float& _m11, const float& _m12, const float& _m13, const float& _m14,
        const float& _m21, const float& _m22, const float& _m23, const float& _m24,
        const float& _m31, const float& _m32, const float& _m33, const float& _m34,
        const float& _m41, const float& _m42, const float& _m43, const float& _m44
    ) :
        m11(_m11), m12(_m12), m13(_m13), m14(_m14),
        m21(_m21), m22(_m22), m23(_m23), m24(_m24),
        m31(_m31), m32(_m32), m33(_m33), m34(_m34),
        m41(_m41), m42(_m42), m43(_m43), m44(_m44)
    {
    }

    // 平行移動
    Matrix Matrix::translate(const Vector3& vec)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m41 = vec.x;
        tmp.m42 = vec.y;
        tmp.m43 = vec.z;
        return tmp;
    }
    Matrix Matrix::translate(const float x, const float y, const float z)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m41 = x;
        tmp.m42 = y;
        tmp.m43 = z;
        return tmp;
    }
    // x軸回転
    Matrix Matrix::rotateX(const float angle)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m22 =  std::cos(angle);
        tmp.m23 =  std::sin(angle);
        tmp.m32 = -std::sin(angle);
        tmp.m33 =  std::cos(angle);
        return tmp;
    }
    // y軸回転
    Matrix Matrix::rotateY(const float angle)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m11 =  std::cos(angle);
        tmp.m13 = -std::sin(angle);
        tmp.m31 =  std::sin(angle);
        tmp.m33 =  std::cos(angle);
        return tmp;
    }
    // z軸回転
    Matrix Matrix::rotateZ(const float angle)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m11 =  std::cos(angle);
        tmp.m12 =  std::sin(angle);
        tmp.m21 = -std::sin(angle);
        tmp.m22 =  std::cos(angle);
        return tmp;
    }
    // 拡大縮小
    Matrix Matrix::scale(const float scale)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m11 = scale;
        tmp.m22 = scale;
        tmp.m33 = scale;
        return tmp;
    }
    Matrix Matrix::scale(const float scaleX, const float scaleY, const float scaleZ)
    {
        Matrix tmp = Matrix::Identify;
        tmp.m11 = scaleX;
        tmp.m22 = scaleY;
        tmp.m33 = scaleZ;
        return tmp;
    }
    // 転置
    Matrix Matrix::transpose(const Matrix matrix)
    {
        return Matrix(
            matrix.m11, matrix.m21, matrix.m31, matrix.m41,
            matrix.m12, matrix.m22, matrix.m32, matrix.m42,
            matrix.m13, matrix.m23, matrix.m33, matrix.m43,
            matrix.m14, matrix.m24, matrix.m34, matrix.m44
        );
    }
    // 左手座標系ビュー行列の作成
    Matrix Matrix::LookAtLH(const Vector3 cameraPos, const Vector3 cameraTarget, const Vector3 cameraUpVec)
    {
        Vector3 zAxis = Vector3(cameraTarget - cameraPos).normalize();
        Vector3 xAxis = Vector3(cameraUpVec.cross(zAxis)).normalize();
        Vector3 yAxis = zAxis.cross(xAxis);

        return Matrix(
            xAxis.x, yAxis.x, zAxis.x, 0.0f,
            xAxis.y, yAxis.y, zAxis.y, 0.0f,
            xAxis.z, yAxis.z, zAxis.z, 0.0f,
            -xAxis.dot(cameraPos), -yAxis.dot(cameraPos), -zAxis.dot(cameraPos), 1.0f
        );
    }
    // 左手座標系パースペクティブ射影行列を作成
    Matrix Matrix::perspectiveFovLH(float fieldOfViewY, float aspectRatio, float znearPlane, float zfarPlane)
    {
        float h = 1.0f / std::tan(fieldOfViewY / 2.0f);
        float w = h / aspectRatio;

        return Matrix(
               w, 0.0f,                                               0.0f, 0.0f,
            0.0f,    h,                                               0.0f, 0.0f,
            0.0f, 0.0f,               zfarPlane / (zfarPlane - znearPlane), 1.0f,
            0.0f, 0.0f, -znearPlane * zfarPlane / (zfarPlane - znearPlane), 0.0f
        );
    }



    const Matrix Matrix::Zero(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    );
    const Matrix Matrix::Identify(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}