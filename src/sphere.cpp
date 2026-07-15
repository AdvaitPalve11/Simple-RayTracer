#include "sphere.h"
#include <cmath>
Sphere::Sphere(const Vec3& center , double radius) : center(center) , radius(radius){}

bool Sphere::hit(const Ray& ray, double& t) const{

    Vec3 oc = ray.getOrigin() - center; // OC = O - C
    

    double a = ray.getDirection().dot(ray.getDirection()); // a = D . D
    double b = 2.0 * oc.dot(ray.getDirection()); // b = 2 (D . OC)
    double c = oc.dot(oc) - radius * radius; // c = OC . OC - r^2
    double discriminant = b * b - 4 * a * c; // b^2 - 4ac

    if(discriminant < 0)
        return false;
    
    double sqrtD = std::sqrt(discriminant);

    double t1 = (-b - sqrtD) / (2 * a);
    double t2 = (-b + sqrtD) / (2 * a);

    if (t1 > 0){
        t = t1;
        return true;
    }

    if (t2 > 0){
        t = t2;
        return true;
    }

    return false;
}