#pragma once

#include <memory>
#include<vector>

#include "light.h"
#include "hittable.h"

class Scene {

    private:
        std::vector<std::shared_ptr<Hittable>> objects;
        std::vector<std::shared_ptr<Light>> lights;
    
    public:
        void add(const std::shared_ptr<Hittable>& objects);

        bool hit(const Ray& ray , HitRecord& record) const;

        void addLight(const std::shared_ptr<Light>& light);

        const std::vector<std::shared_ptr<Light>>& getLights() const;
};