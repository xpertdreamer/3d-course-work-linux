#ifndef FLAME_H
#define FLAME_H

#include "VAO.h"
#include "VBO.h"
#include "shaderClass.h"
#include <vector>
#include "Camera.hpp"

class Flame
{
public:
    struct Layer
    {
        VAO vao;
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        float radius;
        float height;
        float colorR;
    };

    std::vector<Layer> layers;

    Flame();
    void addLayer(float radius, float height, float colorR);
    void Draw(Shader& shader, Camera& camera, const matrix4& modelMatrix, float time);
    void Delete();
};

#endif
