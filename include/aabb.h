#pragma once

#include "vec3.h"
#include "ray.h"

class AABB
{
private:
    Vec3 minimum;
    Vec3 maximum;

public:
    AABB();
    AABB(const Vec3& minimum, const Vec3& maximum);

    bool hit(const Ray& ray, double tMin, double tMax) const;

    const Vec3& getMin() const;
    const Vec3& getMax() const;
    static AABB surroundingBox(const AABB& box1, const AABB& box2);
};