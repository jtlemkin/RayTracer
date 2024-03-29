//
// Created by James Lemkin on 12/6/19.
//

#include "Camera.h"

Camera::Camera() : fromPoint(0, 0, -3), atPoint(0, 0, 2), upVector(0, 1, 0), viewingAngle(20) {
  //Viewing angle should be less than 90 degrees

  nearClippingDepth = -fromPoint.z - 0.5f;
  farClippingDepth = -fromPoint.z + 0.5f;

  D = 1 / (2.0f * std::tan(viewingAngle * PI / 180));

  computeBasisVectors();
}

Ray Camera::computeRayAt(int i, int j, int N) {
  Vector3 pixEyePos = Vector3((double) i / (double) N - 0.5f, (double) j / (double) N - 0.5f, D);

  double pixWorldX = b1.dot(pixEyePos) + fromPoint.x;
  double pixWorldY = b2.dot(pixEyePos) + fromPoint.y;
  double pixWorldZ = b3.dot(pixEyePos) + fromPoint.z;

  Vector3 pixWorldPos = Vector3(pixWorldX, pixWorldY, pixWorldZ);

  Vector3 rayDir = (pixWorldPos - fromPoint).normalize();

  return Ray(pixWorldPos, rayDir);
}

const Vector3 &Camera::getFromPoint() const {
  return fromPoint;
}

void Camera::moveRight() {
  Vector3 dir(0.1, 0 , 0);

  fromPoint += dir;

  computeBasisVectors();
}

void Camera::moveLeft() {
  Vector3 dir(-0.1, 0 , 0);

  fromPoint += dir;

  computeBasisVectors();
}

void Camera::moveUp() {
  Vector3 dir(0, 0.1 , 0);

  fromPoint += dir;

  computeBasisVectors();
}
void Camera::moveDown() {
  Vector3 dir(0, -0.1 , 0);

  fromPoint += dir;

  computeBasisVectors();
}
void Camera::computeBasisVectors() {
  b3 = (atPoint - fromPoint).normalize();
  b1 = b3.cross(upVector).normalize();
  b2 = b1.cross(b3);
}
