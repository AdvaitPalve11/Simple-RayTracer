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
    Renderer renderer;

    Uint64 previousTime = SDL_GetPerformanceCounter();

    while (window.processEvents())
    {

    Uint64 currentTime = SDL_GetPerformanceCounter();

    double deltaTime =
        (currentTime - previousTime) /
        static_cast<double>(SDL_GetPerformanceFrequency());

     previousTime = currentTime;

    
     const bool* keyboard = SDL_GetKeyboardState(nullptr);
     const double speed = 5.0 * deltaTime;

     if (keyboard[SDL_SCANCODE_W])
    renderer.getCamera().moveForward(speed);

    if (keyboard[SDL_SCANCODE_S])
        renderer.getCamera().moveForward(-speed);

    if (keyboard[SDL_SCANCODE_A])
        renderer.getCamera().moveRight(-speed);

    if (keyboard[SDL_SCANCODE_D])
        renderer.getCamera().moveRight(speed);

    if (keyboard[SDL_SCANCODE_SPACE])
        renderer.getCamera().moveUp(speed);

    if (keyboard[SDL_SCANCODE_LCTRL])
        renderer.getCamera().moveUp(-speed);
    
    constexpr double sensitivity = 0.12;

        renderer.getCamera().rotate(
        window.getMouseDeltaX() * sensitivity,
        -window.getMouseDeltaY() * sensitivity );

        renderer.render(framebuffer);

        window.present(framebuffer);



    }

    return 0;
}