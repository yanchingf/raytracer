
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

using Point3 = vec3;
using Color = vec3;

struct Ray {

    Point3 origin;
    vec3 direction;

    Ray(Point3& o, vec3& d) : origin(o), direction(d) {}

    vec3 at(double t) const{
        return origin + direction * t;
    }



};

#endif