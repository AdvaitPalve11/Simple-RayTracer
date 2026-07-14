#include <iostream>
#include "Vec3.h"
#include "ray.h"
int main()
{
    Vec3 a;
    Vec3 b(1, 2, 3);
    Vec3 c = a+b;
    Vec3 d = a-b;
    Vec3 x (1,0,0);
    Vec3 y (0,1,0);
   
    Vec3 z = Vec3::cross(x,y);

    a.print();
    b.print();
    c.print();
    d.print();

   
    z.print();

    std::cout<<d.length();

   

    return 0;
}