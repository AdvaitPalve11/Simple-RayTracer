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
        
    

};