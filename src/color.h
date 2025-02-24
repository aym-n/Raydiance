#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"

using color = vec3;
void print_color(std::ostream &out, color &colors)
{
  // get the value and convert it into range [0, 255];
  auto r = int(255.999 * colors.x());
  auto g = int(255.999 * colors.y());
  auto b = int(255.999 * colors.z());

  out << r << ' ' << g << ' ' << b << std::endl;
}

#endif  // !COLOR_H
