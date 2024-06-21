#include "cameraControl.h"
#include <iostream>

CameraControl::CameraControl() {

}

CameraControl::~CameraControl() {

}

void CameraControl::onMouse(int button, int action, double xpos, double ypos) {
    // 判断当前的按键是否按下
    bool pressed = action == GLFW_PRESS;
    // 如果按下，记录当前按下的位置
    if (pressed) {
        mCurrentX = xpos;
        mCurrentY = ypos;
    }
    // 根据鼠标按键的状态，更新鼠标按键的状态
    switch (button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseDown = pressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseDown = pressed;
            break;
    }
}

void CameraControl::onCursor(double xpos, double ypos) {

}

void CameraControl::onKey(int key, int action, int mods) {
    // 过滤掉repeat的情况
    if (action == GLFW_REPEAT) {
        return;
    }
    // 检测是按下还是抬起
    bool pressed = action == GLFW_PRESS;
    // 记录在keyMap
    mKeyMap[key] = pressed;
}

void CameraControl::update() {
}
