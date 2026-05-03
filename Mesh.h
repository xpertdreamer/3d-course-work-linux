#ifndef MESH_H_
#define MESH_H_

#include "Matrix.hpp"
#include "shaderClass.h"
#include "string"

#include "VAO.h"
#include "VBO.h"
#include "Camera.hpp"
#include "Texture.h"
#include <vector>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO vao;

    Mesh
    (
        std::vector<Vertex>& vertices,
        std::vector<GLuint>& indices,
        std::vector<Texture>& textures
     );

    void Draw
    (
        Shader& shader,
        Camera& camera,
        matrix4& model
    );
};

#endif
