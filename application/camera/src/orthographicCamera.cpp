#include "orthographicCamera.h"

OrthographicCamera::OrthographicCamera(float l, float r, float b, float t, float n, float f) {
    mLeft = l;
    mRight = r;
    mTop = t;
    mBottom = b;
    mNear = n;
    mFar = f;
}

OrthographicCamera::~OrthographicCamera() {

}

glm::mat4 OrthographicCamera::getProjectionMatrix() const {
    return glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}
