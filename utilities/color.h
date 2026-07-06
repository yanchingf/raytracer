
# ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include <iostream>

using color = vec3;

void write_color(const color& pixel_color){

    auto r = pixel_color.r();
    auto g = pixel_color.g();
    auto b = pixel_color.b();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}

# endif