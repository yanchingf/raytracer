
#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

struct Hittable_List : Hittable {

    std::vector<std::shared_ptr<Hittable>> objs;

    Hittable_List() {}
    Hittable_List(std::shared_ptr<Hittable> obj) {add(objs);}

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

};

#endif