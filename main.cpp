
// js copied from tutorial, example loop

#include <iostream>
#include <filesystem>

#include "utilities/color.h"
#include "utilities/vec3.h"


struct Point3 : vec3{};
struct Color : vec3 {};

int main() {

    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
           auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
           write_color(pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";
}

