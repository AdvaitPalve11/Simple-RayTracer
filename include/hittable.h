#pragma once

#include "ray.h"
#include "hitRecord.h"

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray&, HitRecord&) const = 0;
};