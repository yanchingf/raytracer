
#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h" 

struct Material {
    virtual ~Material() = default;

    virtual bool scatter(
        const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered
    ) const = 0;
};

struct Lambertian : Material {
    Color albedo;

    Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const override {
        vec3 scatter_direction = rec.n + randomUnitVector();

        // catch degenerate scatter direction (near-zero vector)
        if (scatter_direction.length() < 1e-8)
            scatter_direction = rec.n;

        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

struct Metal : Material {
    Color albedo;
    double fuzz;

    Metal(const Color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    bool scatter(const Ray& r_in, const Hit_Record& rec, Color& attenuation, Ray& scattered) const override {
        vec3 reflected = reflect(r_in.direction.normalized(), rec.n);
        reflected = reflected.normalized() + (fuzz * randomUnitVector());
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction, rec.n) > 0; 
    }
};

#endif