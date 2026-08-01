
#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "color.h"

#include <limits>
#include <iostream>

struct Camera {

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    double focal_length = 1.0;
    int max_depth = 10; // max num of times ray bounces

    int image_height;
    Point3 center;
    Point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

    Camera (int image_w) {

        image_width = image_w;
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);
        
        center = Point3(0, 0, 0);

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0); // v goes down from top pixel

        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        Point3 upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = upper_left + (pixel_delta_u * 0.5) + (pixel_delta_v * 0.5);
    }

    Ray getRay(int i, int j) const {
        Point3 pixel_center = pixel00_loc + (pixel_delta_u * i) + (pixel_delta_v * j);
        vec3 ray_direction = pixel_center - center;
        return Ray(center, ray_direction);
    }

    Color rayColor(const Ray& r, const Hittable& world) const {
        Hit_Record rec;
        if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
            return 0.5 * (rec.n + Color(1, 1, 1));
        }
        vec3 unit_direction = r.direction.normalized();
        double a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }

    void render(const Hittable& world) {
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                Ray r = getRay(i, j);
                Color pixel_color = rayColor(r, world);
                write_color(pixel_color);
            }
        }
        std::clog << "\rDone.                 \n";
    }

};

#endif