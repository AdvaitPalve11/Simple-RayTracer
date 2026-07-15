#pragma once

#include <SDL3/SDL.h>
#include <string>

class Window{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int width;
        int height;

    public:
        Window(int w , int h , const std::string& title);
        ~Window();

        bool processEvents();

        void clear();

        void present();
};