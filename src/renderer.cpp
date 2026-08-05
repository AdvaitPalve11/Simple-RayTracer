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
}



Vec3 Renderer::trace(const Ray& ray, int depth)
{
    if (depth <= 0)
        return Vec3(0.0, 0.0, 0.0);

    HitRecord record;

    if (scene.hit(ray, record)){

        const auto& lights = scene.getLights();
        double brightness = 0.15;

        for (const auto& light : lights){
            Vec3 lightPosition = light->getPosition();
            Vec3 lightDirection = (lightPosition - record.point).normalized();
            Vec3 viewDirection = -ray.getDirection();
            Vec3 reflectionDirection = (-lightDirection).reflect(record.normal);

            Vec3 shadowOrigin = record.point + record.normal * 0.001;
            Ray shadowRay(shadowOrigin, lightDirection);

            HitRecord shadowRecord;

            double lightDistance = (lightPosition - record.point).length();

            bool inShadow = scene.hit(shadowRay, shadowRecord) && shadowRecord.t < lightDistance;

            if (!inShadow) {
                double diffuse = std::max(0.0, record.normal.dot(lightDirection));
                double specular = std::pow(std::max(0.0, reflectionDirection.dot(viewDirection)), 32.0);

                double intensity = light->getIntensity();
                brightness += diffuse * intensity;
                brightness += specular * intensity;

            }
        }

        

        Vec3 color = record.material.getColor();
        Vec3 finalColor = color * brightness;

        MaterialType type = record.material.getType();
        
        if (type == MaterialType::Diffuse)
            return finalColor;
        

        if (type == MaterialType::Metal){

            double reflectivity = record.material.getReflectivity();

            Vec3 reflectedDirection = ray.getDirection().normalized().reflect(record.normal);
            reflectedDirection = (reflectedDirection + Vec3::randomUnitVector() * record.material.getRoughness()).normalized();

            Vec3 reflectionOrigin = record.point + record.normal * 0.001;

            Ray reflectedRay(reflectionOrigin, reflectedDirection);

            Vec3 reflectedColor = trace(reflectedRay, depth - 1);

            Vec3 metalReflection = reflectedColor * color;

            return finalColor * (1.0 - reflectivity) +  metalReflection * reflectivity;
            
        }

        if (type == MaterialType::Glass)
            return finalColor;
        

        return finalColor;

    }


    Vec3 direction = ray.getDirection();
    double blend = 0.5 * (direction.y + 1.0);

    Vec3 white(1.0, 1.0, 1.0);
    Vec3 blue(0.5, 0.7, 1.0);

    return white * (1.0 - blend) + blue * blend;
}




void Renderer::render(Framebuffer& framebuffer)
{
    Uint64 start = SDL_GetPerformanceCounter();

    // Multithreading
    const unsigned int threadCount = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

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

    std::cout << ms << " ms\n";
}

void Renderer::renderRows(Framebuffer& framebuffer, int startY, int endY)
{
    const int width = framebuffer.getWidth();
    const int height = framebuffer.getHeight();

    const int samples = 4;

    for (int y = startY; y < endY; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Vec3 color(0.0, 0.0, 0.0);

            for (int i = 0; i < samples; i++)
            {
                thread_local static std::mt19937 rng(std::random_device{}());
                thread_local static std::uniform_real_distribution<double> dist(0.0, 1.0);

                double offsetX = dist(rng);
                double offsetY = dist(rng);

                double u = (x + offsetX) / (width - 1);
                double v = (y + offsetY) / (height - 1);

                Ray ray = camera.getRay(u, v);

                color = color + trace(ray, 4);
            }

            color = color / samples;

            color.x = std::sqrt(std::clamp(color.x, 0.0, 1.0));
            color.y = std::sqrt(std::clamp(color.y, 0.0, 1.0));
            color.z = std::sqrt(std::clamp(color.z, 0.0, 1.0));

            uint8_t r = static_cast<uint8_t>(std::clamp(color.x, 0.0, 1.0) * 255.0);
            uint8_t g = static_cast<uint8_t>(std::clamp(color.y, 0.0, 1.0) * 255.0);
            uint8_t b = static_cast<uint8_t>(std::clamp(color.z, 0.0, 1.0) * 255.0);

            framebuffer.setPixel(x, y, (255u << 24) | (r << 16) | (g << 8) | b);
        }
    }
}