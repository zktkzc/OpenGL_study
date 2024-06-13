#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "wrapper/include/checkError.h"
#include "application/include/Application.h"

void OnResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void OnKeyBoard(int key, int action, int mods) {
    std::cout << "key: " << key << " action: " << action << " mods: " << mods << std::endl;
}

void prepare() {
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    // 生成一个VBO
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));
    // 绑定当前VBO，到OpenGL状态机的当前VBO插槽上，GL_ARRAY_BUFFER表示当前vbo这个插槽
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    // 向当前VBO传输数据，也是在开辟显存
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
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
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f))

    prepare();

    // 执行窗体循环
    while (application->update()) {
        // 执行OpenGL画布清理操作
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
    }

    // 退出程序前做相关清理
    application->destroy();
    return 0;
}
