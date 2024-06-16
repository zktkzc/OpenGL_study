#pragma once

#include "core.h"
#include <string>

class Shader {
public:
    Shader(const char *vertexPath, const char *fragmentPath);

    ~Shader();

    void begin() const;

    void end() const;

    void setFloat(const std::string &name, float value) const;

    void setVector3(const std::string &name, float x, float y, float z) const;

    void setVector3(const std::string &name, const float* values) const;

private:
    static void checkShaderErrors(GLuint target, const std::string &type);

private:
    GLuint mProgram{0};
};