#include "window.h"
#include <iostream>
#include <string>
#include <sstream>

Window::Window(int w , int h ,const  std::string& title): width(w), height(h) {

    if(!SDL_Init(SDL_INIT_VIDEO))
        std::cout << SDL_GetError() << '\n';

        
    window = SDL_CreateWindow(title.c_str(),width,height,SDL_WINDOW_RESIZABLE);
        if(!window)
            std::cout<<SDL_GetError() << "\n";

    renderer = SDL_CreateRenderer(window,nullptr);
        if(!renderer)
            std::cout<<SDL_GetError()<<"\n";

    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,width,height);
        if(!texture)
            std::cout<<SDL_GetError()<<"\n";

    lastTime = SDL_GetTicks();
    frameCount = 0;



}

Window::~Window(){
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::processEvents(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){

        if(event.type == SDL_EVENT_QUIT)
            return false;
    }

    return true;
}

void Window::clear(){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    SDL_RenderClear(renderer);
}

void Window::present(const Framebuffer& framebuffer){

    SDL_UpdateTexture(texture, nullptr, framebuffer.data() , framebuffer.getWidth() * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    frameCount++;

    Uint64 currentTime = SDL_GetTicks();

    if (currentTime - lastTime >= 1000){

        double fps = frameCount * 1000.0 / (currentTime - lastTime);

        std::stringstream title;
        title << "Ray Tracer | FPS: " << static_cast<int>(fps);

        SDL_SetWindowTitle(window, title.str().c_str());

        frameCount = 0;
        lastTime = currentTime;
    }
}