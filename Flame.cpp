#include "Flame.h"
#include "EBO.h"

Flame::Flame()
{
    addLayer(0.18f, 1.2f, 0.0f);
    addLayer(0.12f, 1.5f, 0.5f);
    addLayer(0.06f, 1.8f, 1.0f);
}

void Flame::addLayer(float radius, float height, float colorR)
{
    Layer layer;
    layer.radius = radius;
    layer.height = height;
    layer.colorR = colorR;

    const int segments = 12;
    Vertex tip;
    tip.position[0] = 0.f;
    tip.position[1] = -height;
    tip.position[2] = 0.f;
    tip.color[0] = colorR; tip.color[1] = 0.f; tip.color[2] = 0.f;
    layer.vertices.push_back(tip);

    for (int i = 0; i <= segments; i++)
    {
        float angle = 2.f * 3.14159f * i / segments;
        Vertex v;
        v.position[0] = radius * cosf(angle);
        v.position[1] = 0.f;
        v.position[2] = radius * sinf(angle);
        v.color[0] = colorR; v.color[1] = 0.f; v.color[2] = 0.f;
        layer.vertices.push_back(v);
    }

    for (int i = 1; i <= segments; i++)
    {
        layer.indices.push_back(0);      // кончик
        layer.indices.push_back(i);
        layer.indices.push_back(i + 1);
    }

    layer.vao.Bind();
    VBO vbo(layer.vertices);
    EBO ebo(layer.indices);
    
    layer.vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    layer.vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    layer.vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    layer.vao.LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    
    layer.vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
    
    layers.push_back(std::move(layer));
}

void Flame::Draw(Shader& shader, Camera& camera, const matrix4& modelMatrix, float time)
{
    shader.Activate();
    camera.Matrix(shader, "camMatrix");
    glUniform1f(glGetUniformLocation(shader.ID, "time"), time);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"),
                       1, GL_FALSE, modelMatrix.data());
    
    for (int i = 0; i < (int)layers.size(); i++)
    {
        float intensity = 1.0f - i * 0.5f; // внешний тусклее
        glUniform1f(glGetUniformLocation(shader.ID, "flameIntensity"), intensity);
        
        layers[i].vao.Bind();
        glDrawElements(GL_TRIANGLES,
                       (GLsizei)layers[i].indices.size(),
                       GL_UNSIGNED_INT, 0);
        layers[i].vao.Unbind();
    }
}

void Flame::Delete()
{
    for (auto& l : layers) l.vao.Delete();
}
