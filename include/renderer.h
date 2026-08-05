#pragma once

#include <cstdint>
#include "camera.h"
#include "framebuffer.h"
#include "scene.h"

class Renderer{
public:
    Renderer();

    void render(Framebuffer& framebuffer);

private:
    Camera camera;
    Scene scene;
    uint32_t rayColor(const Ray& ray);
};