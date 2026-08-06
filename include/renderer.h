#pragma once

#include <cstdint>
#include "camera.h"
#include "framebuffer.h"
#include "scene.h"

class Renderer{
public:
    Renderer();
    Camera& getCamera();

    void render(Framebuffer& framebuffer);
    void renderRows(Framebuffer& framebuffer, int startY, int endY);
    void buildPrimaryRays(int width, int height);
    

private:
    Camera camera;
    Scene scene;
   Vec3 trace(const Ray& ray, int depth);
   std::vector<Ray> primaryRays;

};