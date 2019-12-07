//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SCENE_H
#define HW5_SCENE_H

#include <vector>
#include <iostream>
#include <optional>
#include "Sphere.h"
#include "Ray.h"
#include "PixelBuffer.h"
#include "Camera.h"
#include "Intersection.h"

class Scene {
 public:
  Camera camera;

  Scene();

  void addSphere(float x, float y, float z, float radius, float r, float g, float b);
  void setAmbientColor(float r, float g, float b);

  void writeToBuffer(PixelBuffer& buffer);

  std::optional<Intersection> computeClosestIntersection(const Ray& ray) const;

 private:
  std::vector<Sphere> spheres;
  Color ambient;
  Light light;
};

#endif //HW5_SCENE_H
