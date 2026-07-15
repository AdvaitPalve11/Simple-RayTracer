#include "framebuffer.h"
#include "renderer.h"
#include<iostream>

#include <vector>
Renderer::Renderer(int width , int height): width(width) , height(height){}

void Renderer::render(Framebuffer& framebuffer){

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double u = static_cast<double>(x) / (width-1);
            double v = static_cast<double>(y) / (height -1);

            uint8_t r = static_cast<uint8_t>(255*u);
            uint8_t g = static_cast<uint8_t>(255*v);
            uint8_t b = 128;

            uint32_t color = (255 << 24) | (r <<16) | (g << 8) | b;

            framebuffer.setPixel(x,y,color);
        }
        
    }
    
}