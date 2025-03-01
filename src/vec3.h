#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "constants.h"

class vec3
{
public:
  double e[3];
  vec3() : e{0, 0, 0} {}
  vec3(double x, double y, double z) : e{x, y, z} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }  // Read access -> double x = v[0];
  double &operator[](int i) { return e[i]; }       // Write access -> v[0] = 5;

  vec3 operator+=(const vec3 &v)
  {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
  }

  vec3 &operator*=(double t)
  {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
  }

  vec3 &operator/=(double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  bool near_zero() const
  {
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
  }

  static vec3 random() { return vec3(random_double(), random_double(), random_double()); }

  static vec3 random(double min, double max) { return vec3(random_double(min, max), random_double(min, max), random_double(min, max)); }
};

// Using Point3 as an alias for Vec3
using point3 = vec3;

inline std::ostream &operator<<(std::ostream &out, const vec3 &v) { return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << ' '; }

inline vec3 operator+(const vec3 &u, const vec3 &v) { return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]); }

inline vec3 operator-(const vec3 &u, const vec3 &v) { return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]); }

inline vec3 operator*(const vec3 &u, const vec3 &v) { return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]); }

inline vec3 operator*(double t, const vec3 &v) { return vec3(t * v.e[0], t * v.e[1], t * v.e[2]); }

inline vec3 operator*(const vec3 &v, double t) { return t * v; }

inline vec3 operator/(const vec3 &u, double t) { return (1 / t) * u; }

// Dot and Cross product
inline double dot(const vec3 &u, const vec3 &v) { return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]; }

inline vec3 cross(const vec3 &u, const vec3 &v)
{
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1], u.e[2] * v.e[0] - u.e[0] * v.e[2], u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

inline vec3 random_unit_vector()
{
  while (true)
  {
    auto p = vec3::random(-1, 1);
    auto lensq = p.length_squared();
    if (1e-160 < lensq && lensq <= 1)
      return p / sqrt(lensq);
  }
}

inline vec3 random_on_hemisphere(const vec3 &normal)
{
  vec3 unit_vec = random_unit_vector();
  if (dot(unit_vec, normal) > 0.0)
    return unit_vec;
  return -unit_vec;
}

inline vec3 reflect(const vec3 &v, const vec3 &n) { return v - 2 * dot(v, n) * n; }

inline vec3 refract(const vec3 &uv, const vec3 &n, double ri)
{
  auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec3 r_perp = ri * (uv + cos_theta * n);
  vec3 r_parallel = -std::sqrt(fabs(1.0 - r_perp.length_squared())) * n;
  return r_parallel + r_perp;
}

#endif  // !VEC3_H
