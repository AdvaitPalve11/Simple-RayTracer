#include <iostream>
#include "renderer.h"
#include "Vec3.h"
#include "ray.h"
#include <SDL3/SDL.h>
#include "window.h"

int main()
{
    const int WIDTH = 1280;
    const int HEIGHT = 720;

    Window window(WIDTH, HEIGHT, "RayTracer");
    Framebuffer framebuffer(WIDTH, HEIGHT);
    Renderer renderer(WIDTH, HEIGHT);

    while (window.processEvents())
    {
        renderer.render(framebuffer);

        window.present(framebuffer);
    }

    return 0;
}