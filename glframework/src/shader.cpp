#include "shader.h"
#include "../../wrapper/include/checkError.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 读取shader代码
    std::string vertexCode;
    std::string fragmentCode;
    // 声明用于读取文件的对象
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 保证ifstream对象可以抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // 打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        // 读取文件内容到字符串
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // 关闭文件
        vShaderFile.close();
        fShaderFile.close();
        // 转换为字符串
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
    }

    // 创建shader程序
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // 为shader程序输入shader代码
    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    // 执行shader代码编译
    glCompileShader(vertex);
    // 查看vertex是否正确编译
    checkShaderErrors(vertex, "COMPILE");
    glCompileShader(fragment);
    // 检查fragment是否正确编译
    checkShaderErrors(fragment, "COMPILE");

    // 创建program并附加shader
    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);
    // 链接program
    glLinkProgram(mProgram);
    // 检查program是否正确链接
    checkShaderErrors(mProgram, "LINK");
    // 删除shader，因为它们已经链接到program中了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {

}

void Shader::begin() const {
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end() const {
    GL_CALL(glUseProgram(0));
}

void Shader::checkShaderErrors(GLuint target, const std::string& type) {
    int success = 0;
    char infoLog[1024];
    if (type == "COMPILE") {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    } else if (type == "LINK") {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    } else {
        std::cout << "ERROR::SHADER::UNKNOWN_TYPE" << std::endl;
    }
}

void Shader::setFloat(const std::string &name, float value) const {
    // 通过名称拿到Uniform变量的位置
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    // 通过位置更新Uniform变量的值
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3(const std::string &name, float x, float y, float z) const {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVector3(const std::string &name, const float *values) const {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3fv(location, 1, values));
}

void Shader::setInt(const std::string &name, int value) const {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform1i(location, value));
}

void Shader::setMatrix4x4(const std::string &name, glm::mat4 value) const {
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
}
