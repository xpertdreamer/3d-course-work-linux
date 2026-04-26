#ifndef SHADERCLASS_H_
#define SHADERCLASS_H_

#include "include/glad/glad.h"
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string get_file_contents(const char *filename);

class Shader {
  public:
    GLuint ID;
    Shader(const char *vertexFile, const char *fragmentFile);

    void Activate();
    void Delete();
};

#endif // SHADERCLASS_H_
