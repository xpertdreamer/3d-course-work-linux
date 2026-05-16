#ifndef AXIS_H
#define AXIS_H

#include "shaderClass.h"
#include "Camera.hpp"

class Axis
{
public:
    GLuint VAO;
    GLuint VBO;

    Axis();
    void Draw(Shader& shader, Camera& camera);
    void Delete();
};

#endif
