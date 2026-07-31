
#include <iostream>
#include <filesystem>

#include "utilities/color.h"
#include "utilities/vec3.h"
#include "utilities/ray.h"
#include "utilities/camera.h"

double hit_sphere(const Point3& center, double radius, const Ray& r) {

    vec3 oc = center - r.origin;
    auto a = dot(r.direction, r.direction);
    auto b = -2.0 * dot(r.direction, oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant) ) / (2.0 * a);
    }
}


int main() {

    Camera cam(400); 
    cam.render(world);

}

// g++ main.cpp -o main
// ./main > image.ppm
// open image.ppm