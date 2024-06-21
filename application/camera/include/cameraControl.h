#pragma once

#include <map>
#include "camera.h"

class CameraControl {
public:
    CameraControl();

    ~CameraControl();

    virtual void onMouse(int button, int action, double xpos, double ypos);

    virtual void onCursor(double xpos, double ypos);

    virtual void onKey(int key, int action, int mods);

    virtual void update();

    void setCamera(Camera *camera) { mCamera = camera; }

    void setSensitivity(float sensitivity) { mSensitivity = sensitivity; }

private:
    bool mLeftMouseDown = false;
    bool mRightMouseDown = false;
    bool mMiddleMouseDown = false;
    double mCurrentX = 0.0f, mCurrentY = 0.0f;
    std::map<int, bool> mKeyMap;
    float mSensitivity{0.1f};
    Camera *mCamera = nullptr;
};