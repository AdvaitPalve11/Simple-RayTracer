#include "plane.h"
#include <cmath>

Plane::Plane(const Vec3& point, const Vec3& normal) : point(point),  normal(normal.normalized()){}

bool Plane::hit(const Ray& ray , HitRecord& record)const{
    
   double denominator = ray.getDirection().dot(normal);

   if (std::abs(denominator) < 1e-6)
    return false;

    double t = (point - ray.getOrigin()).dot(normal) / denominator;

    if (t < 0)
        return false;
        
    record.t = t;
    record.point = ray.getOrigin() + ray.getDirection() * t;
    record.normal = normal;
    return true;
}