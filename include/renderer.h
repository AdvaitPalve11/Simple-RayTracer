#pragma once

#include "framebuffer.h"

class Renderer{
public:
    Renderer() = default;

    void render(Framebuffer& framebuffer);

private:
    uint32_t rayColor(double u, double v);
};