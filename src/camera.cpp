#include "camera.h"

Camera::Camera(double fov, double aspectRatio)
    : position(0, 0, 0),
      forward(0, 0, -1),
      up(0, 1, 0),
      right(1, 0, 0),
      fov(fov),
      aspectRatio(aspectRatio)
{
}

Ray Camera::getRay(double u, double v) const
{
    // Convert screen coordinates [0,1] to viewport coordinates [-1,1]
    double viewportX = (2.0 * u - 1.0) * aspectRatio;
    double viewportY = 1.0 - 2.0 * v;

    Vec3 direction(viewportX, viewportY, -1.0);

    direction = direction.normalized();

    return Ray(position, direction);
}

Vec3 Camera::getPosition() const
{
    return position;
}