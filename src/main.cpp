#include <iostream>
#include "renderer.h"
#include "Vec3.h"
#include "ray.h"
#include <SDL3/SDL.h>
#include "window.h"

int main()
{
   Window window(1280,720,"RayTracer");

    while(window.processEvents()){
        window.clear();
        window.present();
    }

    return 0;
}