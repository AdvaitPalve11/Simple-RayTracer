#pragma once

#include "vec3.h"
#include "material.h"

struct HitRecord
{
    double t;
    Vec3 point;
    Vec3 normal;
    Material material;
};