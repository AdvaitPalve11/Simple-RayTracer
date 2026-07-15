#include "renderer.h"
#include "framebuffer.h"


Renderer::Renderer() : camera(90.0, 16.0 / 9.0), sphere(Vec3(0,0,-5),1.0){}

// Returns the color for a ray
uint32_t Renderer::rayColor(const Ray& ray){
    double t;

    if (sphere.hit(ray, t))
        return 0xFFFF0000;

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