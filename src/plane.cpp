#include "plane.h"
#include <cmath>

Plane::Plane(const Vec3& point, const Vec3& normal, const Material& material)
    : point(point),
      normal(normal.normalized()),
      material(material)
{
}

bool Plane::hit(const Ray& ray, HitRecord& record) const
{
    double denominator = ray.getDirection().dot(normal);

    if (std::abs(denominator) < 1e-6)
        return false;

    double t = (point - ray.getOrigin()).dot(normal) / denominator;

    const double epsilon = 0.001;

    if (t < epsilon)
        return false;

    record.t = t;
    record.point = ray.at(t);
    record.normal = normal;
    record.material = material;

    return true;
}