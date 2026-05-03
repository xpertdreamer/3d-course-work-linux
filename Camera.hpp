#ifndef CAMERA_H_
#define CAMERA_H_

#include "Matrix.hpp"
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaderClass.h"


class Camera
{
    public:
        float Position[3];
        float Orientation[3] = {0.f, 0.f, -1.f};
        float Up[3] = {0.f, 1.f, 0.f};
        matrix4 cameraMatrix = createIdentityMatrix();

        int width;
        int height;

        float speed = 0.01f;
        float sensitivity = 1.f;

        bool firstClick;
        
        Camera
        (
            int width,
            int height,
            float position[3]
        );

        void updateMatrix
        (
            float FOVdeg,         
            float nearPlane,
            float farPlane
         );
        
        void Matrix
        (    
            Shader& shader,
            const char* uniform
         );
        
        void Inputs
        (
            GLFWwindow* window
        );
};

#endif
