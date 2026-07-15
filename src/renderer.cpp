#include "framebuffer.h"
#include "renderer.h"

void Renderer::render(Framebuffer& framebuffer){
        int width = framebuffer.getWidth();
        int height = framebuffer.getHeight();

    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){

            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            framebuffer.setPixel(x, y, rayColor(u, v));
         }
    }  
}