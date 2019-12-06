//
// Created by James Lemkin on 12/5/19.
//

#include "Scene.h"

Scene::Scene() : eyeLoc(Vector3(1, 1, 1)) {}

void Scene::render() {
  Ray ray = Ray(0, 0, 0, 1, 1, 1);
  addSphere(0, 0, 0, 1);

  float t = computeClosestIntersection(ray);

  std::cout << ray.getPointAt(t);
}

float Scene::computeClosestIntersection(Ray ray) {
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
