#include<vec3.h>
#include<ray.h>

class sphere {
    private:
        Vec3 origin;
        double radius;
        
    public:
    sphere(const Vec3& o , double r) : origin(o) , radius(r){}


    bool hit(const Ray& ray)const;
};