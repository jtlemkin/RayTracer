//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_COLOR_H
#define HW5_COLOR_H

class Color {
 public:
  float r, g, b;

  Color(float r, float g, float b);

  void operator+=(const Color& c2);
};

#endif //HW5_COLOR_H
