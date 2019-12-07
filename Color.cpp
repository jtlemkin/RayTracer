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
