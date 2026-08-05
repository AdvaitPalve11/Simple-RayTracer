#include <memory>
#include <cmath>
#include <algorithm>

#include "renderer.h"
#include "framebuffer.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "hitRecord.h"
#include "vec3.h"
#include "material.h"

Renderer::Renderer(): camera(90.0, 16.0 / 9.0)
{
    scene.add(std::make_shared<Sphere>(
        Vec3(0, 0, -5),
          1.0 ,  
          Material(Vec3(0.7, 0.7, 0.7), MaterialType::Metal, 0.8, 0.5)
        ));

    scene.add(std::make_shared<Plane>(
        Vec3(0, -1, 0), Vec3(0, 1, 0) ,  Material(Vec3(0.6,0.6,0.6) ,  MaterialType::Diffuse)));

    scene.addLight(std::make_shared<Light>( Vec3(5, 5, 0), Vec3(1, 1, 1), 1.0 ));
}



Vec3 Renderer::trace(const Ray& ray, int depth)
{
    if (depth <= 0)
        return Vec3(0.0, 0.0, 0.0);

    HitRecord record;

    if (scene.hit(ray, record)){

        const auto& lights = scene.getLights();
        double brightness = 0.1;

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

                brightness += diffuse;
                brightness += specular * 0.6;
            }
        }

        brightness = std::min(brightness, 1.0);

        Vec3 color = record.material.getColor();
        Vec3 finalColor = color * brightness;

        MaterialType type = record.material.getType();
        
        if (type == MaterialType::Diffuse)
            return finalColor;
        

        if (type == MaterialType::Metal){
            double reflectivity = record.material.getReflectivity();

            Vec3 reflectedDirection = ray.getDirection().reflect(record.normal).normalized();
            Vec3 reflectionOrigin = record.point + record.normal * 0.001;

            Ray reflectedRay(reflectionOrigin, reflectedDirection);

            Vec3 reflectedColor = trace(reflectedRay, depth - 1);

            return finalColor * (1.0 - reflectivity) + reflectedColor * reflectivity;
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
    const int width = framebuffer.getWidth();
    const int height = framebuffer.getHeight();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double u = static_cast<double>(x) / (width - 1);
            double v = static_cast<double>(y) / (height - 1);

            Ray ray = camera.getRay(u, v);

            Vec3 color = trace(ray, 3);

            uint8_t r = static_cast<uint8_t>(std::clamp(color.x, 0.0, 1.0) * 255.0);
            uint8_t g = static_cast<uint8_t>(std::clamp(color.y, 0.0, 1.0) * 255.0);
            uint8_t b = static_cast<uint8_t>(std::clamp(color.z, 0.0, 1.0) * 255.0);

            framebuffer.setPixel(x, y, (255u << 24) | (r << 16) | (g << 8) | b);
        }
    }
}