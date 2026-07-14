#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "renderer.h"
#include<iostream>
#include <filesystem>

#include <vector>
Renderer::Renderer(int width , int height): width(width) , height(height){}

void Renderer::render(){

    std::cout << "Current Path: "<< std::filesystem::current_path()<< '\n';

    std::vector<unsigned char> image(width*height*3); // 1.44 MB memory


    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            
            //convert pixel coords to values btw 0 & 1
            double u = static_cast<double>(x) / (width-1);
            double v = static_cast<double>(y) / (height-1);
            
            //Convert to RGB values ( 0 to 255)
            unsigned char r = static_cast<unsigned char>(255*u);
            unsigned char g =  static_cast<unsigned char>(255*v);
            unsigned char b = 128;

            int index = (y * width + x) * 3;

            image[index + 0] = r;   // R
            image[index + 1] = g;  // G
            image[index + 2] = b;  // B
        }
}


int success = stbi_write_png(
    "../output/image.png",
    width,
    height,
    3,
    image.data(),
    width * 3
);

std::cout << "PNG Write Result: " << success << '\n';
}