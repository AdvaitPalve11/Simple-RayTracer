#pragma once

#include "framebuffer.h"

class Renderer{

    private:
        int width;
        int height;

    public:
        Renderer(int width , int height);

        void render(Framebuffer& framebuffer);
};