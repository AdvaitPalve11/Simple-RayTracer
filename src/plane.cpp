#include "plane.h"
#include <cmath>
#include "aabb.h"

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

AABB Plane::boundingBox() const
{
    const double size = 1000000.0;

    return AABB(
        Vec3(-size, -size, -size),
        Vec3(size, size, size)
    );
}