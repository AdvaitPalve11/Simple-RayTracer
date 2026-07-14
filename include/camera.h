#pragma once

#include "ray.h"

class Camera{

    public:
        Camera();

    Ray getRay(double u , double v) const;
};