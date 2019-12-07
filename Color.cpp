//
// Created by James Lemkin on 12/6/19.
//

#include "Color.h"

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

void Color::operator+=(const Color &c2) {
  r += c2.r;
  g += c2.g;
  b += c2.b;
}
Color Color::operator*(float n) const {
  return Color(r * n, g * n, b * n);
}
Color Color::operator+(const Color &c2) {
  return Color(r + c2.r, g + c2.g, b + c2.b);
}
