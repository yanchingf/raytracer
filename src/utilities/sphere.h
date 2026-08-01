#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include "material.h"

struct Sphere : Hittable {

    Point3 center;
    double radius;
    std::shared_ptr<Material> material;

    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat) : center(center), radius(radius), material(mat) {}

    bool hit(const Ray& r, double t_min, double t_max, Hit_Record& rec) const override {

        vec3 oc = r.origin - center;

        // a*t^2 + b*t + c = 0
        // use quadratic to find hits on sphere
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
        rec.mat = material;

        return true;
    }

    bool BoundingBox(AABB& outputBox) const override {
        outputBox = AABB(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
        return true;
    }
};

#endif