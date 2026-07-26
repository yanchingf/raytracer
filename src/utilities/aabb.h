
#ifndef AABB_H
#define AABB_H

#include "vec3.h"
#include "hittable.h"

#include <algorithm>


struct AABB {

    Point3 min;
    Point3 max;

    AABB () : min(Point3(0, 0, 0)), max(Point3(1, 1, 1)) {}
    AABB (const Point3& min, const Point3& max) : min(min), max(max) {}

    AABB (const AABB& a, const AABB& b) {
        min = Point3(std::min(a.min.x(), b.min.x()), std::min(a.min.y(), b.min.y()), std::min(a.min.z(), b.min.z()));
        min = Point3(std::max(a.max.x(), b.max.x()), std::max(a.max.y(), b.max.y()), std::max(a.max.z(), b.max.z()));
    } 

    bool hit(Ray& r, float t_min, float t_max) const { // calculate if ray hits box
        for (int i = 0; i < 3; ++i){
            float inverse_d = 1.0f / r.direction[i];
            float t_a = (min[i] - r.origin[i]) / inverse_d;
            float t_b = (max[i] - r.origin[i]) / inverse_d;

            if (inverse_d < 0.0){std::swap(t_a, t_b); } // if neg, swap min and max

            t_min = t_a > t_min ? t_a : t_min;
            t_max = t_b < t_max ? t_b : t_max;
            if (t_max <= t_min) {return false; }
            }
            return true;
        }

        int longest_axis() {
            double dx = max[0] - min[0];
            double dy = max[1] - min[1];
            double dz = max[2] - min[2];

            if (dx > dy && dz > dz){
                return 0;
            }
            else if (dy > dx && dy > dz){
                return 1;
            }
            else {
                return 2;
            }
        }

        Point3 centroid () const {return 0.5f * (min + max);}

        double area () const {
            vec3 d = (max - min);
            return 2.0f * (d[0] * d[1] + d[0] * d[2] + d[2] * d[1]);
        }
};


#endif