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

#endif
