#include "scene.h"
#include<limits>

void Scene::add(const std::shared_ptr<Hittable>& object){
    objects.push_back(object);
}

bool Scene::hit(const Ray& ray, HitRecord& record) const{
     bool hitAnything = false;
     double closest = std::numeric_limits<double>::infinity();
     HitRecord tempRecord;

     //check closest hit object by ray
     for(const auto& object : objects){

        if(object->hit(ray , tempRecord)){
            if(tempRecord.t < closest){
                closest= tempRecord.t;
                record = tempRecord;
                hitAnything = true;
            }
        }
     }

     return hitAnything;
}

void Scene::addLight(const std::shared_ptr<Light>& light)
{
    lights.push_back(light);
}

const std::vector<std::shared_ptr<Light>>& Scene::getLights() const
{
    return lights;
}