#pragma once

#include<vec3.h>

class Ray{ // P(t) = O + tD
    private:    
        Vec3 origin;
        Vec3 direction;

    public:
        Ray(const Vec3& o , const Vec3 dir);


    Ray(const Vec3& o , const Vec3& dir) : origin(o) , direction(dir){}

    //getters
    Vec3 getOrigin() const;
    Vec3 getDirection() const;
    Vec3 at(double t) const;
    
};