//
// Created by James Lemkin on 12/6/19.
//

#include "Camera.h"

Camera::Camera() : fromPoint(0, 0, -3), atPoint(0, 0, 2), upVector(0, 1, 0), viewingAngle(55) {
  //Viewing angle should be less than 90 degrees

  nearClippingDepth = -fromPoint.z - 0.5f;
  farClippingDepth = -fromPoint.z + 0.5f;

  D = 1 / (2.0f * (float) std::tan(viewingAngle * PI / 180));

  b3 = (atPoint - fromPoint).normalize();
  b1 = b3.cross(upVector).normalize();
  b2 = b1.cross(b3);
}
