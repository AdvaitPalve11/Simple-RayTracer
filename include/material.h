#pragma once

#include "vec3.h"
#include "materialType.h"

class Material
{
private:
    Vec3 color;
    MaterialType type;

    double reflectivity;
    double roughness;
    double refractiveIndex;
    double emissionStrength;

    Vec3 emissionColor;

public:
    Material();

    Material(
        const Vec3& color,
        MaterialType type = MaterialType::Diffuse,
        double reflectivity = 0.0,
        double roughness = 0.0
    );

    Vec3 getColor() const;
    MaterialType getType() const;
    double getReflectivity() const;
    double getRoughness() const;
};