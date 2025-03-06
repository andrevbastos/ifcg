#pragma once

#include <glad/glad.h>

class Shader {
  public:
    GLuint ID;
    Shader(const char *vertexFile, const char *fragmentFile);

    void activate();
    void destroy();
};
