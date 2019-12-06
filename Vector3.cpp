#include "Vector3.h"

Vector3 Vector3::normalize() {
  float mag = magnitude();

  return Vector3(x / mag, y / mag, z / mag);
}

float Vector3::magnitude() {
  return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator-(Vector3 v2) {
  return Vector3(x - v2.x, y - v2.y, z - v2.z);
}

float Vector3::operator*(Vector3 v2) {
  return x * v2.x + y * v2.y + z * v2.z;
}
Vector3 Vector3::operator*(float s) {
  return Vector3(x * s, y * s, z * s);
}
