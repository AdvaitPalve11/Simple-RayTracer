#pragma once

#include "hittable.h"
#include "vec3.h"

class Plane : public Hittable
{
private:
    Vec3 point;
    Vec3 normal;

public:
    Plane(const Vec3& point, const Vec3& normal);

    bool hit(const Ray& ray, HitRecord& record) const override;
};