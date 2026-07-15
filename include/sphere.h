#include<vec3.h>
#include<ray.h>

class Sphere {
    private:
        Vec3 center;
        double radius;
        
    public:
    Sphere(const Vec3& center , double radius);


    bool hit(const Ray& ray, double& t) const;

};