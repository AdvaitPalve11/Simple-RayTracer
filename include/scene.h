#pragma once

#include <memory>
#include<vector>

#include "hittable.h"

class Scene {

    private:
        std::vector<std::shared_ptr<Hittable>> objects;
    
    public:
        void add(const std::shared_ptr<Hittable>& objects);

        bool hit(const Ray& ray , HitRecord& record) const;
};