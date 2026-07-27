
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

    BVNHNode () {}
    BVNHNode (std::vector<std::shared_ptr<Hittable>>& objs, size_t start, size_t end) {

        int axis = 0;

        auto comparator = boxcompareZ;

        if (axis == 0){
            comparator = boxcompareX;
        }
        else if (axis == 1){
            comparator = boxcompareY;
        }

        size_t span = end - start; // number of objs in this node

        if (span == 1) {left = right = objs[start]; }
        else if (span == 2) {
            left = objs[start];
            right = objs[start + 1];

            if (comparator(left, right)) {std::swap(left, right); }
        }
        else { // split into more nodes
            std::sort(objs.begin() + start, objs.begin() + end, comparator);
            size_t mid = start + span / 2;
            left  = std::make_shared<BVNHNode>(objs, start, mid);
            right = std::make_shared<BVNHNode>(objs, mid, end);
        }

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

struct BVNHTree : Hittable {

    std::shared_ptr<BVNHNode> root;

    BVNHTree() {}
    BVNHTree(std::vector<std::shared_ptr<Hittable>> objs) {
        root = std::make_shared<BVNHNode>(objs, 0, objs.size());
    }

    bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const override {
        return root->hit(r, t_min, t_max, rec);
    }

    bool BoundingBox(AABB& outputBox) const override {
        return root->BoundingBox(outputBox);
    }
    
};

#endif