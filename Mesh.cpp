#include "Mesh.h"
#include "EBO.h"
#include "Matrix.hpp"
#include "Texture.h"
#include "shaderClass.h"
#include <string>

Mesh::Mesh
(
    std::vector<Vertex>& vertices,
    std::vector<GLuint>& indices,
    std::vector<Texture>& textures
)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vao.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO(vertices);
    // Generates Element Buffer Object and links it to indices
    EBO EBO(indices);

    // Links VBO attributtes such as coord and color to VAO
    vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    // Unbind all to prevent accidentally modifying them
    vao.Unbind();
    VBO.Unbind();
    EBO.Unbind();
}

void Mesh::Draw
(
    Shader& shader,
    Camera& camera,
    matrix4& model
)
{
    shader.Activate();
    vao.Bind();

    int modelLoc = glGetUniformLocation(shader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string uniformName = "tex" + std::to_string(i);
        textures[i].texUnit(shader, uniformName.c_str(), i);
        textures[i].Bind();
    }

    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
