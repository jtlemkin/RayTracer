//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_CAMERA_H
#define HW5_CAMERA_H

#include "Vector3.h"
#include "Ray.h"

#define PI 3.14159265

class Camera {
 private:
  Vector3 fromPoint;
  Vector3 atPoint;
  Vector3 upVector;

  double viewingAngle;
  double nearClippingDepth;
  double farClippingDepth;

  //distance from screen
  double D;

  //basis vectors
  Vector3 b1;
  Vector3 b2;
  Vector3 b3;
  
  void computeBasisVectors();

 public:
  Camera();

  Ray computeRayAt(int i, int j, int N);

  const Vector3 &getFromPoint() const;

  void moveRight();
  void moveLeft();
  void moveUp();
  void moveDown();
};

#endif //HW5_CAMERA_H
