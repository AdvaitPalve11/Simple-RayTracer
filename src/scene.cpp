#include "scene.h"

void Scene::add(const std::shared_ptr<Hittable>& object){
    objects.push_back(object);
}