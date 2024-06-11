#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "wrapper/include/checkError.h"
#include "application/include/Application.h"

int main() {
    if (!application->init()) {
        return -1;
    }

    // 设置opengl视口以及清理颜色
    GL_CALL(glViewport(0, 0, application->getWidth(), application->getHeight()));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f))

    // 执行窗体循环
    while (application->update()) {
        // 执行OpenGL画布清理操作
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
    }

    // 退出程序前做相关清理
    application->destroy();
    return 0;
}
