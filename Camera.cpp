//
// Created by James Lemkin on 12/6/19.
//

#include "Camera.h"

Camera::Camera() : fromPoint(0, 0, -3), atPoint(0, 0, 2), upVector(0, 1, 0), viewingAngle(20) {
  //Viewing angle should be less than 90 degrees

  nearClippingDepth = -fromPoint.z - 0.5f;
  farClippingDepth = -fromPoint.z + 0.5f;

  D = 1 / (2.0f * (float) std::tan(viewingAngle * PI / 180));

  b3 = (atPoint - fromPoint).normalize();
  b1 = b3.cross(upVector).normalize();
  b2 = b1.cross(b3);
}

Ray Camera::computeRayAt(int i, int j, int N) {
  Vector3 pixEyePos = Vector3((float) i / (float) N - 0.5f, (float) j / (float) N - 0.5f, D);

  float pixWorldX = b1.dot(pixEyePos) + fromPoint.x;
  float pixWorldY = b2.dot(pixEyePos) + fromPoint.y;
  float pixWorldZ = b3.dot(pixEyePos) + fromPoint.z;

  Vector3 pixWorldPos = Vector3(pixWorldX, pixWorldY, pixWorldZ);

  Vector3 rayDir = (pixWorldPos - fromPoint).normalize();

  return Ray(pixWorldPos, rayDir);
}
const Vector3 &Camera::getFromPoint() const {
  return fromPoint;
}
