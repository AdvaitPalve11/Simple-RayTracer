#pragma once

#include<vector>
#include <cstdint>

class Framebuffer{

    private:
        int width;
        int height;

        std::vector<uint32_t> pixels;


    public:
        Framebuffer(int width, int height);

        void clear(uint32_t color);

        void setPixel(int x , int y , uint32_t color);

      const  uint32_t* data() const;

        int getWidth() const;
        int getHeight() const;
};