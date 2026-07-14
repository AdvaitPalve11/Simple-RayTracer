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

            int index = (y * width + x) * 3;

            image[index + 0] = 50;   // R
            image[index + 1] = 100;  // G
            image[index + 2] = 255;  // B
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