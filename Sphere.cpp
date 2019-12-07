//
// Created by James Lemkin on 12/5/19.
//

#include "Sphere.h"

Sphere::Sphere(float x, float y, float z, float radius, float r, float g, float b, float specularity = 10) :
    center(Vector3(x, y, z)), radius(radius), color(r, g, b), specularity(specularity) {}

Vector3 Sphere::computeNormalAt(const Vector3 &point) const {
  return Vector3(2 * (point.x - center.x), 2 * (point.y - center.y), 2 * (point.z - center.z)).normalize();
}

Color Sphere::computeColorAt(const Vector3 &point, const Vector3& cameraPos, Light& light, float k) const {

  Color colorAtPoint(0, 0, 0);

  Vector3 normal = computeNormalAt(point);
  Vector3 view = (cameraPos - point).normalize();

  //for (const auto& light : lights) {
    float lightIntensityAtPoint = light.intensity / (view.magnitude() + k);

    Vector3 lightVector = (light.pos - point).normalize();
    Vector3 reflectionVector = (-lightVector + normal * 2 * normal.dot(lightVector)).normalize();

    float amountOfLightHittingPoint = lightVector.dot(normal);
    float amountOfReflectionHittingCamera = reflectionVector.dot(view);

    Color diffuseColor(0, 0, 0);
    Color specularColor(0, 0, 0);

    if (amountOfLightHittingPoint > 0) {
      diffuseColor = color * amountOfLightHittingPoint;

      if (amountOfReflectionHittingCamera > 0) {
        specularColor = light.color * pow(reflectionVector.dot(view), 10);
      }
    }

    colorAtPoint += (diffuseColor + specularColor) * lightIntensityAtPoint;
  //}

  return colorAtPoint;
}

