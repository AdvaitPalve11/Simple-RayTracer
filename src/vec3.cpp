#include "vec3.h"
#include<iostream>
#include<math.h>

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

double Vec3::dot(const Vec3&a , const Vec3& b){
    return  a.x * b.x +a.y * b.y + a.z * b.z;
}


void Vec3::print() const{
    std::cout << "("
              << x << ", "
              << y << ", "
              << z << ")"
              << '\n';
}

