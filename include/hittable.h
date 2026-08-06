#pragma once

#include "ray.h"
#include "hitRecord.h"
#include "aabb.h"

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray&, HitRecord&) const = 0;
    virtual AABB boundingBox() const = 0;
};