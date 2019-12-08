//
// Created by James Lemkin on 12/5/19.
//

#ifndef HW5_SCENE_H
#define HW5_SCENE_H

#include <vector>
#include <iostream>
#include <optional>
#include "Objects/Sphere.h"
#include "Ray.h"
#include "PixelBuffer.h"
#include "Camera.h"
#include "Intersection.h"
#include "Objects/Plane.h"

class Scene {
 public:
  Camera camera;

  Scene();

  void addSphere(double x, double y, double z, double radius, float r, float g, float b);
  void addPlane(double A, double B, double C, double D, float r, float g, float b, float specularity);
  void addLight(double x, double y, double z, float intensity, float r, float g, float b);
  void setAmbientColor(float r, float g, float b);

  void writeToBuffer(PixelBuffer& buffer);

  std::optional<Intersection> computeClosestIntersection(const Ray& ray) const;

 private:
  std::vector<std::unique_ptr<Object>> objects;
  std::vector<Light> lights;
  Color ambient;
};

#endif //HW5_SCENE_H
