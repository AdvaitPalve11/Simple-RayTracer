#include "scene.h"

void Scene::add(const std::shared_ptr<Hittable>& object){
    objects.push_back(object);
}

void Scene::buildBVH()
{
    if (objects.empty())
        return;

    root = std::make_shared<BVHNode>(
        objects,
        0,
        objects.size()
    );
}

bool Scene::hit(const Ray& ray, HitRecord& record) const{
    if (!root)
        return false;

    return root->hit(ray, record);
}

void Scene::addLight(const std::shared_ptr<Light>& light){
    lights.push_back(light);
}

const std::vector<std::shared_ptr<Light>>& Scene::getLights() const{
    return lights;
}