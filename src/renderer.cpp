#include <memory>
#include <algorithm>

#include "renderer.h"
#include "framebuffer.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "hitRecord.h"
#include "vec3.h"

Renderer::Renderer(): camera(90.0, 16.0 / 9.0)
{
    scene.add(std::make_shared<Sphere>(
        Vec3(0, 0, -5),  1.0 ,   Material(Vec3(1.0,0.0,0.0) )));

    scene.add(std::make_shared<Plane>(
        Vec3(0, -1, 0), Vec3(0, 1, 0) ,  Material(Vec3(0.6,0.6,0.6))));

    scene.addLight(std::make_shared<Light>( Vec3(5, 5, 0), Vec3(1, 1, 1), 1.0 ));
}

uint32_t Renderer::rayColor(const Ray& ray)
{
    HitRecord record;

    if (scene.hit(ray, record))
    {
        

        const auto& lights = scene.getLights();
        double brightness = 0.1;

        for (const auto& light : lights){
            Vec3 lightPosition = light->getPosition();

             Vec3 lightDirection = (lightPosition - record.point).normalized();
             Vec3 shadowOrigin =  record.point + record.normal * 0.001;
              Ray shadowRay(shadowOrigin, lightDirection);
              HitRecord shadowRecord;

             double lightDistance = (lightPosition - record.point).length();

             bool inShadow =scene.hit(shadowRay, shadowRecord) &&  shadowRecord.t < lightDistance;

             if (!inShadow)
                 brightness += std::max( 0.0, record.normal.dot(lightDirection));
        


            }

        brightness = std::min(brightness, 1.0);

        Vec3 color = record.material.getColor();

        Vec3 finalColor = color * brightness;

        uint8_t r = static_cast<uint8_t>(std::clamp(finalColor.x, 0.0, 1.0) * 255.0);
        uint8_t g = static_cast<uint8_t>(std::clamp(finalColor.y, 0.0, 1.0) * 255.0);
        uint8_t b = static_cast<uint8_t>(std::clamp(finalColor.z, 0.0, 1.0) * 255.0);

        return (255u << 24) |(r << 16) |  (g << 8) |  b;
    }

    Vec3 direction = ray.getDirection();

    double blend = 0.5 * (direction.y + 1.0);

    uint8_t r = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 127);
    uint8_t g = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 178);
    uint8_t b = 255;

    return (255u << 24) |  (r << 16) | (g << 8) | b;
}

void Renderer::render(Framebuffer& framebuffer)
{
    const int width = framebuffer.getWidth();
    const int height = framebuffer.getHeight();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            Ray ray = camera.getRay(u, v);

            framebuffer.setPixel(x, y, rayColor(ray));
        }
    }
}