#include "Camera.hpp"
#include "Matrix.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
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

void Camera::Inputs
(
    GLFWwindow* window
)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position[0] += speed * Orientation[0];
        Position[1] += speed * Orientation[1];
        Position[2] += speed * Orientation[2];
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position[0] += speed * -Orientation[0];
        Position[1] += speed * -Orientation[1];
        Position[2] += speed * -Orientation[2];
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        float crossP[3];
        cross(Orientation, Up, crossP);
        Position[0] -= speed * crossP[0];
        Position[1] -= speed * crossP[1];
        Position[2] -= speed * crossP[2];
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        float crossP[3];
        cross(Orientation, Up, crossP);
        Position[0] += speed * crossP[0];
        Position[1] += speed * crossP[1];
        Position[2] += speed * crossP[2];
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position[0] += speed * Up[0];
        Position[1] += speed * Up[1];
        Position[2] += speed * Up[2];
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position[0] -= speed * Up[0];
        Position[1] -= speed * Up[1];
        Position[2] -= speed * Up[2];
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            glfwSetCursorPos(window, width / 2, height / 2);
            firstClick = false;
        }
        
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

        float right[3];
        cross(Orientation, Up, right);
        normalize(right);

        float newOrientation[3];
        rotateVector(Orientation, right, glm::radians(-rotX), newOrientation);

        float dotProd = newOrientation[0] * Up[0] + newOrientation[1] * Up[1] + newOrientation[2] * Up[2];
        float angle = glm::degrees(std::acos(dotProd));

        if (angle >= 5.f && angle <= 175.f)
        {
            Orientation[0] = newOrientation[0];
            Orientation[1] = newOrientation[1];
            Orientation[2] = newOrientation[2];
        }

        float rotated[3];
        rotateVector(Orientation, Up, glm::radians(-rotY), rotated);

        Orientation[0] = rotated[0];
        Orientation[1] = rotated[1];
        Orientation[2] = rotated[2];
        normalize(Orientation);

        glfwSetCursorPos(window, width / 2, height / 2);
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
