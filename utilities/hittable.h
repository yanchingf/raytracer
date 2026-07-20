
#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct Hit_Record {
    Point3 p;
    vec3 n;
    double t; // t param of ray hit

    bool front_face;

    void set_face(const Ray& r, const vec3& outward){
        front_face = dot(r.direction, outward) < 0;
        n = front_face ? outward : -outward;
    }

};

struct Hittable {

    virtual ~Hittable() = default;
    virtual bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const = 0;

};

#endif