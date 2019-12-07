//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_LIGHT_H
#define HW5_LIGHT_H

#include "Color.h"
#include "Vector3.h"

class Light {
 public:
  Vector3 pos;
  float intensity;
  Color color;

  Light(float x, float y, float z, float intensity, float r, float g, float b);
};

#endif //HW5_LIGHT_H
