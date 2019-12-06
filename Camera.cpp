//
// Created by James Lemkin on 12/6/19.
//

#include "Camera.h"

Camera::Camera() : fromPoint(0, 0, -2), atPoint(0, 0, 2), upVector(0, 1, 0), viewingAngle(110), nearClippingDepth(1.5),
                   farClippingDepth(2.5) {
  b3 = (atPoint - fromPoint).normalize();
  b1 = b3.cross(upVector).normalize();
  b2 = b1.cross(b3);
}