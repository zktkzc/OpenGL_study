#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "checkError.h"
#include "Application.h"

GLuint vao, program;

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void OnKeyBoard(int key, int action, int mods) {
    std::cout << "key: " << key << " action: " << action << " mods: " << mods << std::endl;
}

void prepareVAO() {
    // 准备顶点数据和颜色数据
    float positions[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };
    float colors[] = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
    };
    unsigned int indices[] = {
            0, 1, 2,
    };

    // 创建VBO
    GLuint posVbo, colorVbo;
    GL_CALL(glGenBuffers(1, &posVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GL_CALL(glGenBuffers(1, &colorVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    // 创建EBO
    GLuint ebo;
    GL_CALL(glGenBuffers(1, &ebo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));
    // 创建VAO
    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));
    // 绑定VAO和EBO，加入属性描述信息
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));

    // 解绑VAO
    GL_CALL(glBindVertexArray(0));
}

void prepareShader() {
    // 完成vs与fs的源代码，并装入字符串
    const char *vertexShaderSource =
            "#version 460 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec3 aColor;\n"
            "out vec3 color;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "    color = aColor;\n"
            "}\0";
    const char *fragmentShaderSource =
            "#version 460 core\n"
            "out vec4 FragColor;\n"
            "in vec3 color;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(color, 1.0f);\n"
            "}\0";

    // 创建shader程序
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // 为shader程序输入shader代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
    int success = 0;
    char infoLog[1024];
    // 执行shader代码编译
    glCompileShader(vertex);
    // 查看vertex是否正确编译
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glCompileShader(fragment);
    // 检查fragment是否正确编译
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 创建program并附加shader
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    // 链接program
    glLinkProgram(program);
    // 检查program是否正确链接
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // 删除shader，因为它们已经链接到program中了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void render() {
    // 执行OpenGL画布清理操作
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    // 绑定当前的program
    GL_CALL(glUseProgram(program));
    // 绑定VAO
    GL_CALL(glBindVertexArray(vao));
    // 发出绘制指令
    GL_CALL(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0));
    // 解绑VAO
    GL_CALL(glBindVertexArray(0));
}

int main() {
    if (!application->init()) {
        return -1;
    }

    // 设置窗口大小改变回调
    application->setResizeCallback(OnResize);
    // 设置键盘事件回调
    application->setKeyBoardCallback(OnKeyBoard);

    // 设置opengl视口以及清理颜色
    GL_CALL(glViewport(0, 0, application->getWidth(), application->getHeight()));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    prepareShader();
    prepareVAO();

    // 执行窗体循环
    while (application->update()) {
        render();
    }

    // 退出程序前做相关清理
    application->destroy();
    return 0;
}
