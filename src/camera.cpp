#include "camera.h"

#include <cmath>

namespace
{
    constexpr double PI = 3.14159265358979323846;
    constexpr double DEG_TO_RAD = PI / 180.0;
}

Camera::Camera(double fov, double aspectRatio)
    : position(0.0, 0.0, 0.0),
      worldUp(0.0, 1.0, 0.0),
      yaw(-90.0),
      pitch(0.0),
      fov(fov),
      aspectRatio(aspectRatio)
{
    updateVectors();
}

void Camera::updateVectors(){
    const double yawRad = yaw * DEG_TO_RAD;
    const double pitchRad = pitch * DEG_TO_RAD;

    const double cosPitch = std::cos(pitchRad);

    forward = Vec3(
        std::cos(yawRad) * cosPitch,
        std::sin(pitchRad),
        std::sin(yawRad) * cosPitch
    ).normalized();

    right = forward.cross(worldUp).normalized();
    up = right.cross(forward).normalized();
}

Ray Camera::getRay(double u, double v) const{
    const double scale = std::tan(fov * 0.5 * DEG_TO_RAD);

    const double viewportX = (2.0 * u - 1.0) * aspectRatio * scale;
    const double viewportY = (1.0 - 2.0 * v) * scale;

    const Vec3 direction =
        (forward +
         right * viewportX +
         up * viewportY).normalized();

    return Ray(position, direction);
}

void Camera::moveForward(double distance){
    position = position + forward * distance;
     dirty = true;
}

void Camera::moveRight(double distance){
    position = position + right * distance;
     dirty = true;
}

void Camera::moveUp(double distance){
    position = position + worldUp * distance;
     dirty = true;
}

void Camera::rotate(double deltaYaw, double deltaPitch){
    yaw += deltaYaw;
    pitch += deltaPitch;

    if (pitch > 89.0)
        pitch = 89.0;
    else if (pitch < -89.0)
        pitch = -89.0;

    updateVectors();

    dirty = true;
}

const Vec3& Camera::getPosition() const{
    return position;
}

const Vec3& Camera::getForward() const{
    return forward;
}

bool Camera::isDirty() const{
    return dirty;
}

void Camera::clearDirty(){
    dirty = false;
}