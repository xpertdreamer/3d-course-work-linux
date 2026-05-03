#include "Camera.hpp"
#include "Matrix.hpp"
#include "Texture.h"
#include <glm/trigonometric.hpp>

Camera::Camera(int width, int height, float position[3])
{
    Camera::width = width;
    Camera::height = height;
    for (int i = 0; i < 3; i++)
        Position[i] = position[i];
}

void Camera::Matrix
        (
            float FOVdeg,
            float nearPlane,
            float farPlane,
            Shader& shader,
            const char* uniform
        )
{
    matrix4 projection = createIdentityMatrix();

    projection = createPerspectiveMatrix(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

    float center[3];
    center[0] = Position[0] + Orientation[0];
    center[1] = Position[1] + Orientation[1];
    center[2] = Position[2] + Orientation[2];

    float f[3];
    subtract(center, Position, f);
    normalize(f);

    float s[3];
    cross(f, Up, s);
    normalize(s);

    float u[3];
    cross(s, f, u);

    matrix4 view = {
        s[0], u[0], -f[0], 0.0f,
        s[1], u[1], -f[1], 0.0f,
        s[2], u[2], -f[2], 0.0f,
        -dot(s, Position), -dot(u, Position), dot(f, Position), 1.0f
    };

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, multiplyMatrices(projection, view).data());
}
