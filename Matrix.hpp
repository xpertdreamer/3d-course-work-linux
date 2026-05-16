#ifndef MATRIX_H_
#define MATRIX_H_

#include "math.h"
#include <array>

using matrix4 = std::array<float, 16>;

inline matrix4 createIdentityMatrix() {
    return {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

inline matrix4 multiplyMatrices(const matrix4 &a, const matrix4 &b) {
    matrix4 result{};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
            }
        }
    }
    return result;
}

inline matrix4 createRotationMatrixY(float angleRadians) {
    float cosA = std::cos(angleRadians);
    float sinA = std::sin(angleRadians);

    return {cosA,  0.0f, sinA, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -sinA, 0.0f, cosA, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

inline matrix4 createRotationMatrixX(float angleRadians) {
    float cosA = std::cos(angleRadians);
    float sinA = std::sin(angleRadians);

    return {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosA, -sinA, 0.0f,
        0.0f, sinA, cosA, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

inline matrix4 createRotationMatrixZ(float angleRadians) {
    float cosA = std::cos(angleRadians);
    float sinA = std::sin(angleRadians);

    return {
        cosA, -sinA, 0.0f, 0.0f,
        sinA, cosA, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

inline matrix4 createTranslationMatrix(float x, float y, float z) {
    return {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f, x,    y,    z,    1.0f};
}

inline matrix4 createPerspectiveMatrix(float fovRadians, float aspect,
                                       float near, float far) {
    float tanHalfFov = std::tan(fovRadians / 2.0f);

    matrix4 result{};
    result[0] = 1.0f / (aspect * tanHalfFov);
    result[5] = 1.0f / tanHalfFov;
    result[10] = -(far + near) / (far - near);
    result[11] = -1.0f;
    result[14] = -(2.0f * far * near) / (far - near);

    return result;
}

inline matrix4 createScaleMatrix(float x, float y, float z) {
    matrix4 result{};
    result[0] = x;
    result[5] = y;
    result[10] = z;
    result[15] = 1.0f;
    return result;
}

inline float dot(const float a[3], const float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

inline void cross(const float a[3], const float b[3], float result[3]) {
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

inline void normalize(float v[3]) {
    float len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len; v[1] /= len; v[2] /= len;
}

inline void subtract(const float a[3], const float b[3], float result[3]) {
    result[0] = a[0] - b[0];
    result[1] = a[1] - b[1];
    result[2] = a[2] - b[2];
}

// Rodriges formula
inline void rotateVector(const float v[3], const float axis[3], float angleRad, float result[3]) {
    float cosA = std::cos(angleRad);
    float sinA = std::sin(angleRad);
    
    float dot = v[0] * axis[0] + v[1] * axis[1] + v[2] * axis[2];
    
    float crossP[3];
    cross(axis, v, crossP);
    
    result[0] = v[0] * cosA + crossP[0] * sinA + axis[0] * dot * (1.0f - cosA);
    result[1] = v[1] * cosA + crossP[1] * sinA + axis[1] * dot * (1.0f - cosA);
    result[2] = v[2] * cosA + crossP[2] * sinA + axis[2] * dot * (1.0f - cosA);
}

inline void mulMat4Vec4(const matrix4& m, const float v[4], float out[4]) {
    for (int i = 0; i < 4; i++) {
        out[i] = m[i]*v[0] + m[i+4]*v[1] + m[i+8]*v[2] + m[i+12]*v[3];
    }
}

inline bool invertMatrix(const matrix4& m, matrix4& inv) {
    float det =
        m[0]*(m[5]*m[10]*m[15]-m[5]*m[11]*m[14]-m[9]*m[6]*m[15]+m[9]*m[14]*m[7]+m[13]*m[6]*m[11]-m[13]*m[10]*m[7])
       -m[4]*(m[1]*m[10]*m[15]-m[1]*m[11]*m[14]-m[9]*m[2]*m[15]+m[9]*m[14]*m[3]+m[13]*m[2]*m[11]-m[13]*m[10]*m[3])
       +m[8]*(m[1]*m[6]*m[15]-m[1]*m[7]*m[14]-m[5]*m[2]*m[15]+m[5]*m[14]*m[3]+m[13]*m[2]*m[7]-m[13]*m[6]*m[3])
       -m[12]*(m[1]*m[6]*m[11]-m[1]*m[7]*m[10]-m[5]*m[2]*m[11]+m[5]*m[10]*m[3]+m[9]*m[2]*m[7]-m[9]*m[6]*m[3]);
    if (fabs(det) < 1e-8f) return false;
    float id = 1.0f / det;
    inv[0]  =  (m[5]*m[10]*m[15]-m[5]*m[11]*m[14]-m[9]*m[6]*m[15]+m[9]*m[14]*m[7]+m[13]*m[6]*m[11]-m[13]*m[10]*m[7])*id;
    inv[1]  = -(m[1]*m[10]*m[15]-m[1]*m[11]*m[14]-m[9]*m[2]*m[15]+m[9]*m[14]*m[3]+m[13]*m[2]*m[11]-m[13]*m[10]*m[3])*id;
    inv[2]  =  (m[1]*m[6]*m[15]-m[1]*m[7]*m[14]-m[5]*m[2]*m[15]+m[5]*m[14]*m[3]+m[13]*m[2]*m[7]-m[13]*m[6]*m[3])*id;
    inv[3]  = -(m[1]*m[6]*m[11]-m[1]*m[7]*m[10]-m[5]*m[2]*m[11]+m[5]*m[10]*m[3]+m[9]*m[2]*m[7]-m[9]*m[6]*m[3])*id;
    inv[4]  = -(m[4]*m[10]*m[15]-m[4]*m[11]*m[14]-m[8]*m[6]*m[15]+m[8]*m[14]*m[7]+m[12]*m[6]*m[11]-m[12]*m[10]*m[7])*id;
    inv[5]  =  (m[0]*m[10]*m[15]-m[0]*m[11]*m[14]-m[8]*m[2]*m[15]+m[8]*m[14]*m[3]+m[12]*m[2]*m[11]-m[12]*m[10]*m[3])*id;
    inv[6]  = -(m[0]*m[6]*m[15]-m[0]*m[7]*m[14]-m[4]*m[2]*m[15]+m[4]*m[14]*m[3]+m[12]*m[2]*m[7]-m[12]*m[6]*m[3])*id;
    inv[7]  =  (m[0]*m[6]*m[11]-m[0]*m[7]*m[10]-m[4]*m[2]*m[11]+m[4]*m[10]*m[3]+m[8]*m[2]*m[7]-m[8]*m[6]*m[3])*id;
    inv[8]  =  (m[4]*m[9]*m[15]-m[4]*m[11]*m[13]-m[8]*m[5]*m[15]+m[8]*m[13]*m[7]+m[12]*m[5]*m[11]-m[12]*m[9]*m[7])*id;
    inv[9]  = -(m[0]*m[9]*m[15]-m[0]*m[11]*m[13]-m[8]*m[1]*m[15]+m[8]*m[13]*m[3]+m[12]*m[1]*m[11]-m[12]*m[9]*m[3])*id;
    inv[10] =  (m[0]*m[5]*m[15]-m[0]*m[7]*m[13]-m[4]*m[1]*m[15]+m[4]*m[13]*m[3]+m[12]*m[1]*m[7]-m[12]*m[5]*m[3])*id;
    inv[11] = -(m[0]*m[5]*m[11]-m[0]*m[7]*m[9]-m[4]*m[1]*m[11]+m[4]*m[9]*m[3]+m[8]*m[1]*m[7]-m[8]*m[5]*m[3])*id;
    inv[12] = -(m[4]*m[9]*m[14]-m[4]*m[10]*m[13]-m[8]*m[5]*m[14]+m[8]*m[13]*m[6]+m[12]*m[5]*m[10]-m[12]*m[9]*m[6])*id;
    inv[13] =  (m[0]*m[9]*m[14]-m[0]*m[10]*m[13]-m[8]*m[1]*m[14]+m[8]*m[13]*m[2]+m[12]*m[1]*m[10]-m[12]*m[9]*m[2])*id;
    inv[14] = -(m[0]*m[5]*m[14]-m[0]*m[6]*m[13]-m[4]*m[1]*m[14]+m[4]*m[13]*m[2]+m[12]*m[1]*m[6]-m[12]*m[5]*m[2])*id;
    inv[15] =  (m[0]*m[5]*m[10]-m[0]*m[6]*m[9]-m[4]*m[1]*m[10]+m[4]*m[9]*m[2]+m[8]*m[1]*m[6]-m[8]*m[5]*m[2])*id;
    return true;
}

#endif
