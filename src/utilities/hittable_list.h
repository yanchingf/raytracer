
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

struct Hittable_List : Hittable {

    std::vector<std::shared_ptr<Hittable>> objs;

    Hittable_List() {}
    Hittable_List(std::shared_ptr<Hittable> obj) {add(obj);}

    void clear() {objs.clear();}
    void add(std::shared_ptr<Hittable> obj) {objs.push_back(obj);}

    bool hit(const Ray& r, double ray_tmin, double ray_tmax, Hit_Record& rec) const override {

        Hit_Record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& obj : objs) {
            if (obj->hit(r, ray_tmin, closest_so_far, temp_rec)) {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    bool BoundingBox(AABB& outputBox) const override {
    if (objs.empty()) return false;

    AABB tempBox;
    bool firstBox = true;

    for (const auto& obj : objs) {
        if (!obj->BoundingBox(tempBox)) return false; // if single unbounded obj
        outputBox = firstBox ? tempBox : AABB(outputBox, tempBox);
        firstBox = false;
    }

    return true;
}

};

#endif