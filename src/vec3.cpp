#include "vec3.h"
#include<iostream>
#include<cmath>

Vec3::Vec3() : x(0), y(0),z(0){}
Vec3::Vec3(double x , double y , double z) : x(x), y(y),z(z){}

Vec3 Vec3::operator+(const Vec3& other) const{
    return Vec3(x+other.x,y+other.y, z+other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const{
    return Vec3(x-other.x,y-other.y, z-other.z);
}

Vec3 Vec3::operator*(double scalar) const{
    return Vec3(x * scalar , y * scalar, z * scalar);
}

Vec3 Vec3::operator/(double scalar) const{
    return Vec3( x / scalar, y / scalar, z / scalar);
}


double Vec3::lengthSquared() const{
    return x * x + y * y + z * z;
}

double Vec3::length()const{
    return std::sqrt(lengthSquared());
}

Vec3 Vec3::normalized() const{
    return *this / length();
}

double Vec3::dot(const Vec3& other) const{
    return x * other.x +  y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}


void Vec3::print() const{
    std::cout << "(" << x << ", "<< y << ", " << z << ")"<< '\n';
}

