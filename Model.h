#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Texture.h"
#include "VBO.h"
#include "shaderClass.h"
#include <vector>
#include "OBJLoader.h"

class Model
{
public:
    std::vector<Mesh> meshes;
    std::vector<Texture> textures;

    float translation[3] = {0.f, 0.f, 0.f};
    float scale[3]       = {1.f, 1.f, 1.f};
        
    Model(const char* file)
    {
        std::vector<Vertex> verts;
        std::vector<GLuint> idx;
        if(loadOBJ(file, verts, idx))
            meshes.emplace_back(verts, idx, textures);
    }

    Model(const char* file, std::vector<Texture>& tex)
    {
        textures = tex;
        std::vector<Vertex> verts;
        std::vector<GLuint> idx;
        if (loadOBJ(file, verts, idx))
            meshes.emplace_back(verts, idx, textures);
    }

    void Draw(Shader& shader, Camera& camera) 
    {
        for (auto& m : meshes) {
            m.Draw(shader, camera);
        }
    }
};

#endif
