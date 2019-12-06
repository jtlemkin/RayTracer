//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_CAMERA_H
#define HW5_CAMERA_H

#include "Vector3.h"

class Camera {
 private:
  Vector3 fromPoint;
  Vector3 atPoint;
  Vector3 upVector;

  float viewingAngle;
  float nearClippingDepth;
  float farClippingDepth;

  //basis vectors
  Vector3 b1;
  Vector3 b2;
  Vector3 b3;

 public:
  Camera();
};

#endif //HW5_CAMERA_H
