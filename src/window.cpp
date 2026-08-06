#include "window.h"

#include <iostream>
#include <sstream>

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

Window::Window(int w, int h, const std::string& title)
    : width(w), height(h)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
        std::cout << SDL_GetError() << '\n';

    window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        SDL_WINDOW_RESIZABLE
    );

    if (!window)
        std::cout << SDL_GetError() << '\n';

    renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer)
        std::cout << SDL_GetError() << '\n';

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );

    if (!texture)
        std::cout << SDL_GetError() << '\n';

    // ---------------- ImGui ----------------

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    // ---------------------------------------

    SDL_SetWindowRelativeMouseMode(window, true);

    lastTime = SDL_GetTicks();
    frameCount = 0;
}

Window::~Window()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

bool Window::processEvents()
{
    mouseDeltaX = 0;
    mouseDeltaY = 0;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL3_ProcessEvent(&event);

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            return false;

        case SDL_EVENT_MOUSE_MOTION:
            mouseDeltaX += event.motion.xrel;
            mouseDeltaY += event.motion.yrel;
            break;
        }
    }

    return true;
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::present(const Framebuffer& framebuffer)
{
    // Begin ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // ===============================
    // ImGui Window
    // ===============================

    ImGui::Begin("Ray Tracer");

    ImGui::Text("Hello Dear ImGui!");

    ImGui::Separator();

    ImGui::Text("FPS: %.1f",
        frameCount * 1000.0 /
        std::max(1.0,
            static_cast<double>(SDL_GetTicks() - lastTime)));

    ImGui::End();

    // ===============================

    SDL_UpdateTexture(
        texture,
        nullptr,
        framebuffer.data(),
        framebuffer.getWidth() * sizeof(uint32_t)
    );

    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, texture, nullptr, nullptr);

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData(),
        renderer
    );

    SDL_RenderPresent(renderer);

    frameCount++;

    Uint64 currentTime = SDL_GetTicks();

    if (currentTime - lastTime >= 1000)
    {
        double fps =
            frameCount * 1000.0 /
            (currentTime - lastTime);

        std::stringstream ss;
        ss << "Ray Tracer | FPS: " << static_cast<int>(fps);

        SDL_SetWindowTitle(window, ss.str().c_str());

        frameCount = 0;
        lastTime = currentTime;
    }
}

int Window::getMouseDeltaX() const
{
    return mouseDeltaX;
}

int Window::getMouseDeltaY() const
{
    return mouseDeltaY;
}