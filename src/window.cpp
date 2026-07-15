#include "window.h"
#include <iostream>

Window::Window(int w , int h ,const  std::string& title): width(w), height(h) {

    if(!SDL_Init(SDL_INIT_VIDEO))
        std::cout << SDL_GetError() << '\n';

        
    window = SDL_CreateWindow(title.c_str(),width,height,SDL_WINDOW_RESIZABLE);
        if(!window)
            std::cout<<SDL_GetError() << "\n";

    renderer = SDL_CreateRenderer(window,nullptr);
        if(!renderer)
            std::cout<<SDL_GetError()<<"\n";

}

Window::~Window(){
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

void Window::present(){
    SDL_RenderPresent(renderer);
}