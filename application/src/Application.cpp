#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Application *Application::mInstance = nullptr;

Application::~Application() {

}

Application::Application() {

}

Application *Application::getInstance() {
    if (mInstance == nullptr) {
        mInstance = new Application();
    }
    return mInstance;
}

bool Application::init(const int &width, const int &height) {
    mWidth = width;
    mHeight = height;
    // 初始化glfw基本环境
    glfwInit();
    // 设置glfw的主版本号和次版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // 设置渲染模式为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 创建窗体对象
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", NULL, NULL);
    if (mWindow == nullptr) return false;
    // 设置当前窗体对象为当前上下文对象
    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

    // 将Application对象指针绑定到窗体对象上
    glfwSetWindowUserPointer(mWindow, this);

    // 键盘事件相应
    glfwSetKeyCallback(mWindow, keyCallback);

    return true;
}

bool Application::update() {
    if (glfwWindowShouldClose(mWindow)) {
        return false;
    }
    // 接受并分发窗体消息
    glfwPollEvents();
    // 切换双缓存
    glfwSwapBuffers(mWindow);
    return true;
}

void Application::destroy() {
    glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow *window, int width, int height) {
//    if (Application::getInstance()->mResizeCallback != nullptr)
//        Application::getInstance()->mResizeCallback(width, height);
    Application *self = (Application *) glfwGetWindowUserPointer(window);
    if (self->mResizeCallback != nullptr)
        self->mResizeCallback(width, height);
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Application *self = (Application *) glfwGetWindowUserPointer(window);
    if (self->mKeyBoardCallback != nullptr)
        self->mKeyBoardCallback(key, action, mods);
}
