#include "material.h"

Material::Material()
    : color(1.0, 1.0, 1.0)
{
}

Material::Material(const Vec3& color): color(color)
{
}

Vec3 Material::getColor() const
{
    return color;
}