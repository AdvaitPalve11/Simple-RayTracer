#include<memory>
#include<algorithm>

#include "renderer.h"
#include "framebuffer.h"
#include "sphere.h"
#include "hitRecord.h"
#include "light.h"
#include "vec3.h"


Renderer::Renderer() : camera(90.0, 16.0 / 9.0){
    scene.add(std::make_shared<Sphere>(Vec3(0,0,-5),1.0));
    scene.addLight(std::make_shared<Light>(Vec3(5,5,0), Vec3(1,1,1) , 1.0));
}

// Returns the color for a ray
uint32_t Renderer::rayColor(const Ray& ray){
    
    HitRecord record;

    if (scene.hit(ray, record)){

    Vec3 lightDirection = Vec3(-1, 1, 1).normalized();
    double brightness = record.normal.dot(lightDirection);
    brightness = std::max(0.0, brightness);

    uint8_t intensity = static_cast<uint8_t>(brightness * 255);
    return (255u << 24) |  (intensity << 16) |(intensity << 8) | intensity;

}


    Vec3 direction = ray.getDirection();

    // Map direction.y from [-1, 1] to [0, 1]
    double blend = 0.5 * (direction.y + 1.0);

    // Simple sky gradient
    uint8_t r = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 127);
    uint8_t g = static_cast<uint8_t>((1.0 - blend) * 255 + blend * 178);
    uint8_t b = 255;

    return (255u << 24) | (r << 16) | (g << 8) | b;
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
            const double u = static_cast<double>(x) / (width - 1);
            const double v = static_cast<double>(y) / (height - 1);

            Ray ray = camera.getRay(u, v);

            framebuffer.setPixel(x, y, rayColor(ray));
        }
    }
}