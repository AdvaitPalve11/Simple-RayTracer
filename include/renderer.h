#pragma once

#include <cstdint>
#include "camera.h"
#include "framebuffer.h"

class Renderer{
public:
    Renderer();

    void render(Framebuffer& framebuffer);

private:
    Camera camera;
    uint32_t rayColor(const Ray& ray);
};