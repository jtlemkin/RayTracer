//
// Created by James Lemkin on 12/5/19.
//

#include "Scene.h"

Scene::Scene() : ambient(0, 0, 0) {}

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
        double t = intersection.value().t;

        Vector3 intersectionPoint = ray.getPointAt(t);

        for (const auto& light: lights) {
          Vector3 lightVector = (light.pos - intersectionPoint).normalize();

          Ray shadowFeeler = Ray(intersectionPoint, lightVector);

          auto lightRayIntersection = computeClosestIntersection(shadowFeeler);

          if (!lightRayIntersection.has_value()) {
            pixel += intersectedSphere.computeColorAt(intersectionPoint, camera.getFromPoint(), light, 5);
          } else {
            computeClosestIntersection(shadowFeeler);
          }
        }
      }

      buffer.recordPixel(i, j, pixel);

      //Compute phong color for point
      //I(p) = Idirect + Iglobal

      //Store color in pixel buffer
    }
  }
}

std::optional<Intersection> Scene::computeClosestIntersection(const Ray& ray) const {
  double closest = std::numeric_limits<double>::max();
  int closestSphereIndex;

  for (int i = 0; i < spheres.size(); i++) {
    double intersection = ray.intersect(spheres.at(i));

    //This is to avoid rounding errors
    if (intersection < closest && intersection > 0.0000000000001) {
      closest = intersection;
      closestSphereIndex = i;
    }
  }

  if (closest != std::numeric_limits<double>::max()) {
    const Sphere& closestSphere = spheres.at(closestSphereIndex);
    return Intersection(closestSphere, closest);
  } else {
    return {};
  }
}

void Scene::addSphere(double x, double y, double z, double radius, float r, float g, float b) {
  spheres.emplace_back(x, y, z, radius, r, g, b, 1);
}
void Scene::setAmbientColor(float r, float g, float b) {
  ambient = Color(r, g, b);
}
void Scene::addLight(double x, double y, double z, float intensity, float r, float g, float b) {
  lights.emplace_back(x, y, z, intensity, r, g, b);
}

