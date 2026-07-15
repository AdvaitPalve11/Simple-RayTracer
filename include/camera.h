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
        Camera(double fov, double aspectRatio);

        Ray getRay(double u, double v) const;


        Vec3 getPosition() const;
};