#pragma once

#include"vec3.h"
#include "hittable.h"

class Sphere : public Hittable{
    private:
        Vec3 center;
        double radius;
        
    public:
    Sphere(const Vec3& center , double radius);


   bool hit(const Ray& ray, HitRecord& record) const override;

};