#pragma once

#include "ray.h"
#include "vec3.h"

class Camera{

    private:
        Vec3 position;

        Vec3 forward;
        Vec3 up;
        Vec3 right;

        double fov;
        double aspectRatio;

    public:
        Camera();

    Ray getRay(double u , double v) const;

    void moveForward(double distance);
    void moveRight(double distance);
    void moveUp(double distance);

    void rotateYaw(double angle);
    void rotatePitch(double angle);

    Vec3 getPosition() const;
};