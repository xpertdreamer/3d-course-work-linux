#ifndef AXIS_H
#define AXIS_H

#include "shaderClass.h"
#include "Camera.hpp"
#include "VAO.h"

class Axis
{
public:
    VAO vao;
    std::vector<Vertex>  vertices;
    std::vector<GLuint>  indices;

    Axis();
    void Draw(Shader& shader, Camera& camera);
    void Delete();
};

#endif
