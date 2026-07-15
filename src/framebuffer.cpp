//Framebuffer only stores pixels.

#include "framebuffer.h"
#include <algorithm>

Framebuffer::Framebuffer(int w , int h) : width(w) , height(h) , pixels(width * height){}

void Framebuffer::clear(uint32_t color){
    std::fill(pixels.begin() , pixels.end() , color);
}

void Framebuffer::setPixel(int x , int y , uint32_t color){
    pixels[y * width + x] = color;
}

const uint32_t* Framebuffer::data() const{
    return pixels.data();
}

int Framebuffer::getWidth() const{
    return width;
}

int Framebuffer::getHeight() const{
    return height;
}