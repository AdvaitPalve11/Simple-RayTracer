#pragma once

#include"vec3.h"
#include "hittable.h"

class Sphere : public Hittable{
    private:
        Vec3 center;
        double radius;
        Material material;
        
    public:
        Sphere(const Vec3& center , double radius, const Material& material);


        bool hit(const Ray& ray, HitRecord& record) const override;

        AABB boundingBox() const override;

};