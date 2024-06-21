#include "camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

glm::mat4 Camera::getViewMatrix() const {
    glm::vec3 front = glm::cross(mUp, mRight);
    return glm::lookAt(mPosition, mPosition + front, mUp);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::identity<glm::mat4>();
}
