#include "light.h"

Light::Light(const Vec3& position, const Vec3& color,double intensity) : position(position),color(color), intensity(intensity){}

Vec3 Light::getPosition() const
{
    return position;
}

Vec3 Light::getColor() const
{
    return color;
}

double Light::getIntensity() const
{
    return intensity;
}