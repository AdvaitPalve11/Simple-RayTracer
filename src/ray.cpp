#include "ray.h"
#include "vec3.h"

Ray::Ray(const Vec3& o , const Vec3& dir) : origin(o) , direction(dir){};

Vec3 Ray::getOrigin() const{
    return origin;
}

Vec3 Ray::getDirection() const{
    return direction;
}

Vec3 Ray::at(double t ) const{
    return origin + direction*t;
}
