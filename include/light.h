#pragma once

#include "vec3.h"

class Light{
    private:
    Vec3 position;
    Vec3 color;
    double intensity;

    public:
        Light(const Vec3& position , const Vec3& color , double intensity);

        Vec3 getPosition() const;
        Vec3 getColor() const;
        double getIntensity() const;
};