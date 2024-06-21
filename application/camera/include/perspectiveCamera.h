#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);

    ~PerspectiveCamera();

    glm::mat4 getProjectionMatrix() const override;

private:
    float mFovy{0.0f};
    float mAspect{0.0f};
    float mNear{0.0f};
    float mFar{0.0f};
};