#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "interval.h"
#include "vec3.h"

using color = vec3;
void print_color(std::ostream &out, const color &colors)
{
  auto r = colors.x();
  auto g = colors.y();
  auto b = colors.z();

  static const interval intensity(0.000, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif  // !COLOR_H
