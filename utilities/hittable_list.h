
#ifdef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

struct Hittable_List : Hittable {

    std::vector<shared_ptr<hittable>> objs;

    Hittable_List() {}
    Hittable_List(shared_ptr<hittable> obj) {add(objs);}

    void clear() {objs.clear();}
    void add(shared_ptr<hittable> obj) {objs.push_back(obj);}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record temp_rec;
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