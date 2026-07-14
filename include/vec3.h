#pragma once
// Pragma tells to include this header only once per compilation.

class Vec3
{
    public:
        double x;
        double y;
        double z;

    Vec3() : x(0), y(0) , z(0){}; // Initializer list   
    Vec3(double x , double y , double z) : x(x), y(y),z(z){}; 
        
    //Operations
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar)const;
    Vec3 operator/(double scalar)const;
    

    double length() const;
    double lengthSquared() const;
    Vec3 normalized() const;
    
    static double dot(const Vec3& a, const Vec3& b);


    //misc
    void print() const;
};