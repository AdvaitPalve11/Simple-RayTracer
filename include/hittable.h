//
// Created by Advait on 02-08-2026.
//

#ifndef RAYTRACER_HITTABLE_H
#define RAYTRACER_HITTABLE_H

#include "ray.h"
#include "hitRecord.h"

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& ray, HitRecord& record) const = 0;
};

#endif // RAYTRACER_HITTABLE_H