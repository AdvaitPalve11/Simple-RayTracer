#pragma once

#include <memory>
#include <vector>

#include "hittable.h"
#include "aabb.h"



class BVHNode : public Hittable
{
private:
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;

    AABB box;

public:
    BVHNode();

    BVHNode(
        std::vector<std::shared_ptr<Hittable>>& objects,
        size_t start,
        size_t end
    );

    bool hit(const Ray& ray, HitRecord& record) const override;

    AABB boundingBox() const override;
};