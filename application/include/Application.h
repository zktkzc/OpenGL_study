#pragma once

#include <stdint.h>

#define application Application::getInstance()

class GLFWwindow;

class Application {
public:
    ~Application();

    /**
     * 获取Application实例
     * @return Application实例
     */
    static Application *getInstance();

    /**
     * 获取窗口宽度
     * @return 窗口宽度
     */
    uint32_t getWidth() const { return mWidth; }

    /**
     * 获取窗口高度
     * @return 窗口高度
     */
    uint32_t getHeight() const { return mHeight; }

    bool init(const int &width = 800, const int &height = 600);

    bool update();

    void destroy();

private:
    Application();

private:
    static Application *mInstance;
    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow *mWindow{nullptr};
};