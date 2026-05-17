#include "Axis.h"
#include "VBO.h"
#include "shaderClass.h"

Axis::Axis()
{
    float lenght = 100.f;

    // position            normal          color           texUv
    vertices = {
        // X — red
        Vertex{{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, 0.f}},
        Vertex{{lenght,   0.f, 0.f}, {0.f, 0.f, 0.f}, {1.f, 0.f, 0.f}, {0.f, 0.f}},
        // Y — green
        Vertex{{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        Vertex{{0.f, lenght,   0.f}, {0.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {0.f, 0.f}},
        // Z — blue
        Vertex{{0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
        Vertex{{0.f, 0.f, lenght  }, {0.f, 0.f, 0.f}, {0.f, 0.f, 1.f}, {0.f, 0.f}},
    };

    indices = { 0, 1, 2, 3, 4, 5};

    vao.Bind();
    VBO vbo(vertices);

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
}

void Axis::Draw(Shader& shader, Camera& camera)
{
    shader.Activate();
    vao.Bind();

    glUniform3f(glGetUniformLocation(shader.ID, "camPos"),
                    camera.Position[0], camera.Position[1], camera.Position[2]);
    camera.Matrix(shader, "camMatrix");

    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());

    vao.Unbind();
}

void Axis::Delete()
{
    vao.Delete();
}
