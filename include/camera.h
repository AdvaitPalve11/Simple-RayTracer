#pragma once

#include "ray.h"
#include "vec3.h"

class Camera
{
private:
    // Position
    Vec3 position;

    // Camera orientation
    Vec3 forward;
    Vec3 right;
    Vec3 up;
    Vec3 worldUp;

    // Euler angles
    double yaw;
    double pitch;

    // Camera settings
    double fov;
    double aspectRatio;

    bool dirty = true;

private:
    void updateVectors();

public:
    Camera(double fov, double aspectRatio);

    Ray getRay(double u, double v) const;

    bool isDirty() const;
    void clearDirty();

    // Movement
    void moveForward(double distance);
    void moveRight(double distance);
    void moveUp(double distance);

    // Rotation
    void rotate(double deltaYaw, double deltaPitch);

    // Getters
    const Vec3& getPosition() const;
    const Vec3& getForward() const;
};