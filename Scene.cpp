//
// Created by James Lemkin on 12/5/19.
//

#include "Scene.h"

Scene::Scene() {}

void Scene::writeToBuffer(PixelBuffer &buffer) {
  for (int i = 0; i < buffer.getWidth(); i++) {
    for (int j = 0; j < buffer.getHeight(); j++) {
      //Find the associated ray for each pixel
      Ray ray = camera.computeRayAt(i, j, (int) buffer.getWidth() - 1);

      //Compute closest intersection with object in scene
      //float intersection = computeClosestIntersection(ray);

      //Compute phong color for point

      //Store color in pixel buffer
    }
  }
}

float Scene::computeClosestIntersection(Ray ray) const {
  float closest = std::numeric_limits<float>::max();

  for (const auto& sphere : spheres) {
    float intersection = ray.intersect(sphere);

    closest = intersection < closest ? intersection : closest;
  }

  return closest;
}

void Scene::addSphere(float x, float y, float z, float radius) {
  spheres.emplace_back(x, y, z, radius);
}
