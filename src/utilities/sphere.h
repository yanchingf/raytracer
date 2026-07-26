#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

struct Sphere : Hittable {

    Point3 center;
    double radius;

    Sphere(const Point3& center, double radius) : center(center), radius(radius) {}

    bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const override {

        vec3 oc = r.origin - center;

        // Quadratic coefficients: a*t^2 + b*t + c = 0
        double a = dot(r.direction, r.direction);
        double half_b = dot(oc, r.direction);
        double c = dot(oc, oc) - radius * radius;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;

        double sqrtd = sqrt(discriminant);

        double root = (-half_b - sqrtd) / a;
        if (root < t_min || root > t_max) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || root > t_max)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face(r, outward_normal);

        return true;
    }
};

#endif