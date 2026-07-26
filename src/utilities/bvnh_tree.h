
#ifndef BVNH_TREE_H
#define BVNH_TREE_H

#include "aabb.h"

#include <memory>
#include <vector>
#include <iostream>

struct BVNHNode : Hittable {

    AABB box;
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    int axis;

    BVNHNode () : {}
    BVNHNode (std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end) : {

        int axis = 0;

        if (axis == 0){
            auto comparator = boxcompareX;
        }
        else if (axis == 1){
            auto comparator = boxcompareY;
        }
        else {
            auto comparator = boxcompareZ;
        }

        size_t span = end - start;


    }

    bool BoundingBox(AABB& a) const override {
        a = box;
        return true;
    }

    static bool boxcompare(std::shared_ptr<Hittable>& a, std::shared_ptr<Hittable>& b, int axis) {

        AABB box_a, box_b;
        if (!a->BoundingBox(box_a) || !b->BoundingBox(box_b)){
            std::cout << "Missing box in boxcompare \n";
            return false;
        }
        return box_a.min[axis] < box_b.min[axis];

    }

    static bool boxcompareX(std::shared_ptr<Hittable>& a, std::shared_ptr<Hittable>& b) {
        return boxcompare(a, b, 0);
    }

    static bool boxcompareY(std::shared_ptr<Hittable>& a, std::shared_ptr<Hittable>& b) {
        return boxcompare(a, b, 1);
    }

    static bool boxcompareZ(std::shared_ptr<Hittable>& a, std::shared_ptr<Hittable>& b) {
        return boxcompare(a, b, 2);
    }
    
    
};

struct BVNHTree {
    
};

#endif