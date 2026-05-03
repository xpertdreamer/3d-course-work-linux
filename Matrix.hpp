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

#endif
