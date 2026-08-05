#include "material.h"

Material::Material()
    : color(1.0, 1.0, 1.0),
      type(MaterialType::Diffuse),
      reflectivity(0.0),
      roughness(0.0)
{
}

Material::Material(
    const Vec3& color,
    MaterialType type,
    double reflectivity,
    double roughness)
    : color(color),
      type(type),
      reflectivity(reflectivity),
      roughness(roughness)
{
}

Vec3 Material::getColor() const
{
    return color;
}

MaterialType Material::getType() const
{
    return type;
}

double Material::getReflectivity() const
{
    return reflectivity;
}

double Material::getRoughness() const{
    return roughness;
}