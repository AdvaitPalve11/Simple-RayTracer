#include <iostream>
#include "Vec3.h"

int main()
{
    Vec3 a;

    Vec3 b(1, 2, 3);

    std::cout << a.x << " "
              << a.y << " "
              << a.z << '\n';

    std::cout << b.x << " "
              << b.y << " "
              << b.z << '\n';

    return 0;
}