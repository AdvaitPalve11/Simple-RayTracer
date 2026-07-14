#include <iostream>
#include "Vec3.h"

int main()
{
    Vec3 a;
    Vec3 b(1, 2, 3);
    Vec3 c = a+b;
    Vec3 d = a-b;
    Vec3 adotb = Vec3::cross(a,b);
    Vec3 axb = Vec3::cross(a,b);

    a.print();
    b.print();
    c.print();
    d.print();

    adotb.print();
    axb.print();

    std::cout<<d.length();

    return 0;
}