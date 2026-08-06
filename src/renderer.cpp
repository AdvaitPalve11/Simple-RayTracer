#include <memory>
#include <cmath>
#include <algorithm>
#include <SDL3/SDL.h>
#include <iostream>
#include <thread>
#include <vector>
#include <random>


#include "renderer.h"
#include "framebuffer.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "hitRecord.h"
#include "vec3.h"
#include "material.h"

inline double gammaCorrect(double value){
       value = std::max(0.0, std::min(value, 1.0));
        return std::sqrt(value);
    }

Renderer::Renderer() : camera(60.0, 16.0 / 9.0)
{
    
    scene.add(std::make_shared<Sphere>(
        Vec3(-2.2, 0, -5),
        1.0,
       Material(Vec3(1.0, 0.85, 0.2), MaterialType::Metal, 0.55, 0.02)
    ));

    scene.add(std::make_shared<Sphere>(
        Vec3(0, 0, -5),
        1.0,
        Material(Vec3(0.95, 0.95, 0.95), MaterialType::Metal, 1.0, 0.0)
    ));

    scene.add(std::make_shared<Sphere>(
        Vec3(2.2, 0, -5),
        1.0,
        Material(Vec3(0.2, 0.4, 0.9), MaterialType::Diffuse)
    ));

    scene.add(std::make_shared<Plane>(
        Vec3(0, -1, 0),
        Vec3(0, 1, 0),
        Material(Vec3(0.08, 0.08, 0.8), MaterialType::Diffuse)
    ));

    scene.addLight(std::make_shared<Light>(
        Vec3(5, 5, 0),
        Vec3(1.0, 1,1),
        1
    ));

   scene.addLight(std::make_shared<Light>(
    Vec3(-5,4,3),
    Vec3(0.6,0.7,1.0),
    1.2
));

scene.buildBVH();
}


Camera& Renderer::getCamera()
{
    return camera;
}



Vec3 Renderer::trace(const Ray& ray, int depth)
{
    if (depth <= 0)
        return Vec3(0.0, 0.0, 0.0);

    HitRecord record;

    if (scene.hit(ray, record))
    {
        const Material& material = record.material;
        const auto& lights = scene.getLights();

        double brightness = 0.15;

        for (const auto& light : lights)
        {
            const Vec3 lightPosition = light->getPosition();
            const Vec3 lightDirection = (lightPosition - record.point).normalized();

            Ray shadowRay(
                record.point + record.normal * 0.001,
                lightDirection
            );

            HitRecord shadowRecord;

            const double lightDistance =
                (lightPosition - record.point).length();

            if (!(scene.hit(shadowRay, shadowRecord) &&
                  shadowRecord.t < lightDistance))
            {
                double diffuse =
                    std::max(0.0, record.normal.dot(lightDirection));

                Vec3 reflection =
                    (-lightDirection).reflect(record.normal);

                double specular =
                    std::max(0.0, reflection.dot(-ray.getDirection()));

                specular *= specular;
                specular *= specular;
                specular *= specular;
                specular *= specular;
                specular *= specular;

                const double intensity = light->getIntensity();

                brightness += intensity * (diffuse + specular);
            }
        }

        brightness = std::min(brightness, 1.0);

        const Vec3 color = material.getColor();

        if (material.getType() == MaterialType::Diffuse)
            return color * brightness;

        if (material.getType() == MaterialType::Metal)
        {
            Vec3 reflected =
                ray.getDirection().reflect(record.normal);

            const double roughness = material.getRoughness();

            if (roughness > 0.0)
            {
                reflected =
                    (reflected +
                     Vec3::randomUnitVector() * roughness)
                        .normalized();
            }

            Ray reflectedRay(
                record.point + record.normal * 0.001,
                reflected
            );

            Vec3 reflectedColor =
                trace(reflectedRay, depth - 1);

            return color * brightness * (1.0 - material.getReflectivity())
                 + reflectedColor * color * material.getReflectivity();
        }

        return color * brightness;
    }

    static const Vec3 WHITE(1.0,1.0,1.0);
    static const Vec3 SKY(0.5,0.7,1.0);

    double blend = 0.5 * (ray.getDirection().y + 1.0);

    return WHITE * (1.0 - blend) + SKY * blend;
}




void Renderer::render(Framebuffer& framebuffer)
{

    if (camera.isDirty()){
        buildPrimaryRays(
            framebuffer.getWidth(),
            framebuffer.getHeight()
        );

        camera.clearDirty();
    }

    Uint64 start = SDL_GetPerformanceCounter();

    // Multithreading
    const unsigned int threadCount = std::thread::hardware_concurrency();

    
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    int rowsPerThread = framebuffer.getHeight() / threadCount;

        for (unsigned int i = 0; i < threadCount; i++){

            int startY = i * rowsPerThread;

            int endY = (i == threadCount - 1) ? framebuffer.getHeight() : startY + rowsPerThread;

            threads.emplace_back(&Renderer::renderRows, this, std::ref(framebuffer), startY, endY );
        }

    for (auto& thread : threads)
    {
        thread.join();
    }

    Uint64 end = SDL_GetPerformanceCounter();

    double ms = (end - start) * 1000.0 / SDL_GetPerformanceFrequency();

    static int frame = 0;
    if (++frame % 60 == 0)
            std::cout << ms << " ms\n";
        
}

    
void Renderer::renderRows(
    Framebuffer& framebuffer,
    int startY,
    int endY)
{
    const int width = framebuffer.getWidth();

    constexpr int samples = 1;
    constexpr int depth = 2;

    for (int y = startY; y < endY; y++)
    {
        const int row = y * width;

        for (int x = 0; x < width; x++)
        {
           Vec3 color(0.0, 0.0, 0.0);

            color +=  trace(primaryRays[row + x], depth);
            color /=  samples;

            color.x = gammaCorrect(color.x);
            color.y = gammaCorrect(color.y);
            color.z = gammaCorrect(color.z);

            framebuffer.setPixel(
                x,
                y,
                (255u << 24)
                | (uint32_t(color.x * 255.0) << 16)
                | (uint32_t(color.y * 255.0) << 8)
                | uint32_t(color.z * 255.0)
            );
        }
    }
}

void Renderer::buildPrimaryRays(int width, int height)
{
    primaryRays.clear();
    primaryRays.reserve(width * height);

    const double invWidth  = 1.0 / (width - 1);
    const double invHeight = 1.0 / (height - 1);

    for (int y = 0; y < height; y++)
    {
        const double v = (y + 0.5) * invHeight;

        for (int x = 0; x < width; x++)
        {
            const double u = (x + 0.5) * invWidth;

            primaryRays.emplace_back(camera.getRay(u, v));
        }
    }
}


