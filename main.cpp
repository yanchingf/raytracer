
#include <iostream>
#include <filesystem>

#include "utilities/color.h"
#include "utilities/vec3.h"
#include "utilities/ray.h"

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

Color ray_color(const Ray& r){

    auto t = hit_sphere(Point3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = (r.at(t) - vec3(0,0,-1)).normalized();
        return Color(N.x() + 1, N.y() + 1, N.z() + 1) * 0.5;
    }

    vec3 d = r.direction.normalized();
    auto a = 0.5 * (d.y() + 1.0);
    return Color(1.0, 1.0, 1.0) * (1.0 - a) + Color(0.5, 0.7, 1.0) * a;
    
}

int main() {

    // image
    int image_width = 400;
    auto aspect_ratio = 16.0 / 9.0;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // camera
    auto focal_length = 1.0;
    Point3 cam_center = Point3(0, 0, 0);
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0); // v goes down from top pixel

    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    Point3 upper_left = cam_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2; 
    Point3 pixel00 = upper_left + (pixel_delta_u * 0.5) + (pixel_delta_v * 0.5); // center of pixel at 0,0

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            Point3 pixel_center = pixel00 + (pixel_delta_u * i) + (pixel_delta_v) * j;
            auto ray_direction = pixel_center - cam_center;
            Ray r(cam_center, ray_direction);

            Color pixel_color = ray_color(r);
            write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

// g++ main.cpp -o main
// ./main > image.ppm
// open image.ppm