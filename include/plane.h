#pragma once

#include "hittable.h"
#include "vec3.h"
#include "material.h"

class Plane : public Hittable
{
private:
    Vec3 point;
    Vec3 normal;
    Material material;

public:
    Plane(
        const Vec3& point,
        const Vec3& normal,
        const Material& material
    );

    bool hit(const Ray& ray, HitRecord& record) const override;
};