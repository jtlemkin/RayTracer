#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0) {}

Vector3 Vector3::normalize() const {
  double mag = magnitude();

  if (mag == 0) {
    return *this;
  } else {
    return Vector3(x / mag, y / mag, z / mag);
  }
}

double Vector3::magnitude() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator-(Vector3 v2) const {
  return Vector3(x - v2.x, y - v2.y, z - v2.z);
}

double Vector3::dot(Vector3 v2) const {
  return x * v2.x + y * v2.y + z * v2.z;
}

Vector3 Vector3::operator*(double s) const {
  return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(double s) const {
  return Vector3(x / s, y / s, z /s);
}

Vector3 Vector3::cross(Vector3 v2) const {
  return Vector3(y * v2.z - z * v2.y, z * v2.x - x * v2.z, x * v2.y - y * v2.x);
}

Vector3 Vector3::operator-() const {
  return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(Vector3 v2) const {
  return Vector3(x + v2.x, y + v2.y, z + v2.z);
}
void Vector3::operator+=(Vector3 v2) {
  x += v2.x;
  y += v2.y;
  z += v2.z;
}
double Vector3::angleWith(Vector3 v2) const {
  return acos(dot(v2) / (magnitude() * v2.magnitude()));
}

