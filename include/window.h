#pragma once

#include "framebuffer.h"
#include <SDL3/SDL.h>
#include <string>

class Window{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        int width;
        int height;

        Uint64 lastTime;
        int frameCount;

        //mouse settings
         int mouseDeltaX = 0;
         int mouseDeltaY = 0;

    public:
        Window(int w , int h , const std::string& title);
        ~Window();

        bool processEvents();

        void clear();

        void present(const Framebuffer& framebuffer);

        int getMouseDeltaX() const;
        int getMouseDeltaY() const;

        void resetMouseDelta();
};