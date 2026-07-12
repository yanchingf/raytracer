
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Point3 : vec3{};
stuct Color: vec3{};

struct ray {

    Point3 origin;
    vec3 direction;

    vec3 get_ray(double t){
        return origin + direction * t;
    }



};

#endif