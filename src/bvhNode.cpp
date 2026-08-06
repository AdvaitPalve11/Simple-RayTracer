#include "bvhNode.h"

#include <algorithm>
#include <limits>
#include <cstdlib>

BVHNode::BVHNode()
{
}

AABB BVHNode::boundingBox() const
{
    return box;
}

BVHNode::BVHNode(
    std::vector<std::shared_ptr<Hittable>>& objects,
    size_t start,
    size_t end)
{
    int axis = rand() % 3;

    auto comparator = [axis](const std::shared_ptr<Hittable>& a,
                             const std::shared_ptr<Hittable>& b)
    {
        if (axis == 0)
            return a->boundingBox().getMin().x < b->boundingBox().getMin().x;

        if (axis == 1)
            return a->boundingBox().getMin().y < b->boundingBox().getMin().y;

        return a->boundingBox().getMin().z < b->boundingBox().getMin().z;
    };

    size_t span = end - start;

    if (span == 1)
    {
        left = right = objects[start];
    }
    else if (span == 2)
    {
        if (comparator(objects[start], objects[start + 1]))
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start,
                  objects.begin() + end,
                  comparator);

        size_t mid = start + span / 2;

        left = std::make_shared<BVHNode>(objects, start, mid);
        right = std::make_shared<BVHNode>(objects, mid, end);
    }

    box = AABB::surroundingBox(
        left->boundingBox(),
        right->boundingBox());
}

bool BVHNode::hit(const Ray& ray, HitRecord& record) const
{
    if (!box.hit(ray, 0.001, std::numeric_limits<double>::infinity()))
        return false;

    HitRecord leftRecord;
    HitRecord rightRecord;

    bool hitLeft = left->hit(ray, leftRecord);

    bool hitRight = right->hit(
        ray,
        rightRecord);

    if (hitLeft && hitRight)
    {
        record = (leftRecord.t < rightRecord.t)
                     ? leftRecord
                     : rightRecord;

        return true;
    }

    if (hitLeft)
    {
        record = leftRecord;
        return true;
    }

    if (hitRight)
    {
        record = rightRecord;
        return true;
    }

    return false;
}