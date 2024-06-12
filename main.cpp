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
    // 创建一个VBO，还没有真正分配显存
    GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));
    // 销毁一个VBO
    GL_CALL(glDeleteBuffers(1, &vbo));
    // 创建n个VBO
    GLuint vobArr[] = {0, 0, 0};
    GL_CALL(glGenBuffers(3, vobArr));
    // 销毁n个VBO
    GL_CALL(glDeleteBuffers(3, vobArr));
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
