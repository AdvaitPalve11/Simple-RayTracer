#include <memory>
#include <algorithm>

#include "renderer.h"
#include "framebuffer.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"
#include "hitRecord.h"
#include "vec3.h"

Renderer::Renderer()
    : camera(90.0, 16.0 / 9.0)
{
    // Objects
    scene.add(std::make_shared<Sphere>(
        Vec3(0, 0, -5),
        1.0
    ));

    scene.add(std::make_shared<Plane>(
        Vec3(0, -1, 0),   // Point on plane
        Vec3(0, 1, 0)     // Upward normal
    ));

    // Light (not used yet)
    scene.addLight(std::make_shared<Light>(
        Vec3(5, 5, 0),
        Vec3(1, 1, 1),
        1.0
    ));
}

// Returns the color seen by a ray
uint32_t Renderer::rayColor(const Ray& ray)
{
    HitRecord record;

    if (scene.hit(ray, record))
    {
        
        // Temporary plane debug color
        if (record.normal.y > 0.99)
        {
            return 0xFF00FF00; // Green plane
        }

       
        // Lambert Diffuse Lighting
        Vec3 lightDirection = Vec3(-1, 1, 1).normalized();

        double brightness = std::max(
            0.0,
            record.normal.dot(lightDirection)
        );

        uint8_t intensity =
            static_cast<uint8_t>(brightness * 255.0);

        return (255u << 24) |
               (intensity << 16) |
               (intensity << 8) |
               intensity;
    }

    
    // Sky Gradien
    Vec3 direction = ray.getDirection();

    double blend = 0.5 * (direction.y + 1.0);

    uint8_t r = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 127);
    uint8_t g = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 178);
    uint8_t b = 255;

    return (255u << 24) |
           (r << 16) |
           (g << 8) |
           b;
}


// Render one frame
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