#pragma once

#include "vec3.h"

struct HitRecord
{
    Vec3 point;
    Vec3 normal;
    double t;
};