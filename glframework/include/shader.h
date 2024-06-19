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

    void setVector3(const std::string &name, const float *values) const;

    void setInt(const std::string &name, int value) const;

    void setMatrix4x4(const std::string& name, glm::mat4 value) const;

private:
    static void checkShaderErrors(GLuint target, const std::string &type);

private:
    GLuint mProgram{0};
};