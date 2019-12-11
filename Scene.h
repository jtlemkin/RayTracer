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

  void addSphere(double x, double y, double z, double radius, float r, float g, float b, float indexOfRefraction);
  void addPlane(double A, double B, double C, double D, float r, float g, float b, float specularity, float indexOfRefraction);
  void addLight(double x, double y, double z, float intensity, float r, float g, float b);
  void setAmbientColor(float r, float g, float b);

  void writeToBuffer(PixelBuffer& buffer);

  std::optional<Intersection> intersectRay(const Ray &ray) const;

  Color computeRayColor(const Ray &ray, int level = 0) const;
  Color computeRefractedColor(const Intersection& intersection, const Ray& ray, int level, const Vector3& view,
                              const Vector3& normal) const;

  Object& getLastObject();

 private:
  std::vector<std::unique_ptr<Object>> objects;
  std::vector<Light> lights;
  Color ambient;
};

#endif //HW5_SCENE_H
