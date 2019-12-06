//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SCENE_H
#define HW5_SCENE_H

#include <vector>
#include <iostream>
#include "Sphere.h"
#include "Ray.h"
#include "PixelBuffer.h"

class Scene {
 public:
  Scene();

  void addSphere(float x, float y, float z, float radius);

  void writeToBuffer(PixelBuffer& buffer);

  float computeClosestIntersection(Ray ray) const;
  float computeRayAt(int i, int j, int N, float D) const;
 private:
  std::vector<Sphere> spheres;

  Vector3 eyeLoc;
};

#endif //HW5_SCENE_H
