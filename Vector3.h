//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_POINT_H
#define HW5_POINT_H

#include <ostream>
#include <cmath>

class Vector3 {
 public:
  float x, y, z;

  friend std::ostream &operator<<(std::ostream &os, const Vector3 &vector3) {
    os << "(" << vector3.x << "," << vector3.y << "," << vector3.z << ")";
    return os;
  }

  Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

  Vector3 operator-(Vector3 v2);
  float operator*(Vector3 v2);
  Vector3 operator*(float s);

  Vector3 normalize();
  float magnitude();
};

#endif //HW5_POINT_H
