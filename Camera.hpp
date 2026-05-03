#ifndef CAMERA_H_
#define CAMERA_H_

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaderClass.h"


class Camera
{
    public:
        float Position[3];
        float Orientation[3] = {0.f, 0.f, -1.f};
        float Up[3] = {0.f, 1.f, 0.f};

        int width;
        int height;

        float speed = 0.1f;
        float sensitivity = 1.f;

        bool firstClick;
        
        Camera
        (
            int width,
            int height,
            float position[3]
        );

        void Matrix
        (
            float FOVdeg,
            float nearPlane,
            float farPlane,
            Shader& shader,
            const char* uniform
         );
        
        void Inputs
        (
            GLFWwindow* window
        );
};

#endif
