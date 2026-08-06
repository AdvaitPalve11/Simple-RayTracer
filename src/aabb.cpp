#include "aabb.h"
#include <algorithm>

AABB::AABB()
    : minimum(0,0,0),
      maximum(0,0,0) {}

AABB::AABB(const Vec3& minimum, const Vec3& maximum)
    : minimum(minimum),
      maximum(maximum) {}

const Vec3& AABB::getMin() const
{
    return minimum;
}

const Vec3& AABB::getMax() const
{
    return maximum;
}

bool AABB::hit(const Ray& ray, double tMin, double tMax) const{
    
    for (int axis = 0; axis < 3; axis++){
        double origin;
        double direction;
        double minValue;
        double maxValue;

        if (axis == 0){
            origin = ray.getOrigin().x;
            direction = ray.getDirection().x;
            minValue = minimum.x;
            maxValue = maximum.x;
        }
        else if (axis == 1) {
            origin = ray.getOrigin().y;
            direction = ray.getDirection().y;
            minValue = minimum.y;
            maxValue = maximum.y;
        }
        else
        {
            origin = ray.getOrigin().z;
            direction = ray.getDirection().z;
            minValue = minimum.z;
            maxValue = maximum.z;
        }

        double invD = 1.0 / direction;

        double t0 = (minValue - origin) * invD;
        double t1 = (maxValue - origin) * invD;

        if (invD < 0.0)
            std::swap(t0, t1);

        tMin = std::max(t0, tMin);
        tMax = std::min(t1, tMax);

        if (tMax <= tMin)
            return false;

    }

    return true;
}