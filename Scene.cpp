//
// Created by James Lemkin on 12/5/19.
//

#include "Scene.h"

Scene::Scene() : ambient(0, 0, 0), light(10, 5, 0, 10, 0.25, 0.25, 0.25) {}

void Scene::writeToBuffer(PixelBuffer &buffer) {
  for (int i = 0; i < buffer.getSize(); i++) {
    for (int j = 0; j < buffer.getSize(); j++) {
      Color pixel = ambient;

      //Find the associated ray for each pixel
      Ray ray = camera.computeRayAt(i, j, (int) buffer.getSize() - 1);

      //Compute closest intersection with object in scene
      auto intersection = computeClosestIntersection(ray);

      //Try next pixel if no intersection
      if (intersection.has_value()) {
        const Sphere& intersectedSphere = intersection.value().sphere;
        float t = intersection.value().t;

        Vector3 intersectionPoint = ray.getPointAt(t);

        pixel += intersectedSphere.computeColorAt(intersectionPoint, camera.getFromPoint(), light, 5);
      }

      buffer.recordPixel(i, j, pixel);

      //Compute phong color for point
      //I(p) = Idirect + Iglobal

      //Store color in pixel buffer
    }
  }
}

std::optional<Intersection> Scene::computeClosestIntersection(const Ray& ray) const {
  float closest = std::numeric_limits<float>::max();
  int closestSphereIndex;

  for (int i = 0; i < spheres.size(); i++) {
    float intersection = ray.intersect(spheres.at(i));

    if (intersection < closest) {
      closest = intersection;
      closestSphereIndex = i;
    }
  }

  if (closest != std::numeric_limits<float>::max()) {
    const Sphere& closestSphere = spheres.at(closestSphereIndex);
    return Intersection(closestSphere, closest);
  } else {
    return {};
  }
}

void Scene::addSphere(float x, float y, float z, float radius, float r, float g, float b) {
  spheres.emplace_back(x, y, z, radius, r, g, b, 1);
}
void Scene::setAmbientColor(float r, float g, float b) {
  ambient = Color(r, g, b);
}
