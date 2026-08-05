#pragma once

#include "vec3.h"

class Material
{
private:
    Vec3 color;

public:
    Material();
    Material(const Vec3& color);

    Vec3 getColor() const;
};