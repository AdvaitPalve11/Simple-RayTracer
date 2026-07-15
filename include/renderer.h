#pragma once

#include <cstdint>
#include "camera.h"
#include "framebuffer.h"
#include "sphere.h"

class Renderer{
public:
    Renderer();

    void render(Framebuffer& framebuffer);

private:
    Camera camera;
    Sphere sphere;
    uint32_t rayColor(const Ray& ray);
};