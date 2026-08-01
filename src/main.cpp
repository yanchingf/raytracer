
#include <iostream>
#include <filesystem>
#include <memory>

#include "utilities/color.h"
#include "utilities/vec3.h"
#include "utilities/ray.h"
#include "utilities/camera.h"
#include "utilities/hittable_list.h"
#include "utilities/material.h"
#include "utilities/sphere.h"


int main() {

    Hittable_List world = Hittable_List();

    auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);

    world.add(std::make_shared<Sphere>(Point3( 0, -100.5, -1), 100, material_ground));
    world.add(std::make_shared<Sphere>(Point3( 0, 0, -1), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, material_left));

    Camera cam(400); 
    cam.render(world);

}

// g++ src/main.cpp -o main
// ./main > image.ppm
// open image.ppm