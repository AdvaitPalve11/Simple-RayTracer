#include "sphere.h"
#include "material.h"
#include <cmath>

Sphere::Sphere(const Vec3& center , double radius , const Material& material) : center(center) , radius(radius) , material(material) {}

bool Sphere::hit(const Ray& ray, HitRecord& record) const{

    
    Vec3 oc = ray.getOrigin() - center; // OC = O - Cs
    

    double a = ray.getDirection().dot(ray.getDirection()); // a = D . D
    double b = 2.0 * oc.dot(ray.getDirection()); // b = 2 (D . OC)
    double c = oc.dot(oc) - radius * radius; // c = OC . OC - r^2
    double discriminant = b * b - 4 * a * c; // b^2 - 4ac

    if(discriminant < 0)
        return false;
    
    double sqrtD = std::sqrt(discriminant);

    double t1 = (-b - sqrtD) / (2 * a);
    double t2 = (-b + sqrtD) / (2 * a);

    const double epsilon = 0.001;

    if (t1 > epsilon){
        record.t = t1;
        record.point = ray.at(t1);
        record.normal = (record.point - center).normalized();
        record.material = material;
        return true;
    }

    if (t2 > epsilon){
        record.t = t2;
       record.point = ray.at(t2);
        record.normal = (record.point - center).normalized();
        record.material = material;
        return true;
    }

    return false;
}

//AABB Implementation
AABB Sphere::boundingBox() const
{
    Vec3 radiusVec(radius, radius, radius);

    return AABB(center - radiusVec, center + radiusVec);
}