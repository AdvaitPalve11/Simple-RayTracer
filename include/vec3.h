#pragma once
// Pragma tells to include this header only once per compilation.

class Vec3
{
    public:
        double x;
        double y;
        double z;

    Vec3(); // Initializer list   
    Vec3(double x , double y , double z);
    Vec3(double value): x(value), y(value), z(value){}
        
    //Operations
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(double scalar)const;
    Vec3 operator/(double scalar)const;
    
    Vec3 operator-() const;
    

    double length() const;
    double lengthSquared() const;
    Vec3 normalized() const;

   double dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;


    //misc
    void print() const;

    Vec3 reflect(const Vec3& normal) const;

    static Vec3 randomUnitVector();

    Vec3 operator*(const Vec3& other) const;

    Vec3& operator+=(const Vec3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3& operator-=(const Vec3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3& operator*=(double s)
{
    x *= s;
    y *= s;
    z *= s;
    return *this;
}

Vec3& operator/=(double s)
{
    x /= s;
    y /= s;
    z /= s;
    return *this;
}

};