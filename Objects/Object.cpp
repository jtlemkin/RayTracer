//
// Created by James Lemkin on 12/7/19.
//

#include "Sphere.h"
#include "Object.h"

Color Object::computeColorAt(const Vector3 &point, const Vector3& cameraPos, const Light& light, float k) const {
  Color colorAtPoint(0, 0, 0);

  Vector3 normal = computeNormalAt(point);
  Vector3 view = (cameraPos - point).normalize();

  double lightIntensityAtPoint = light.intensity / (view.magnitude() + k);

  Vector3 lightVector = (light.pos - point).normalize();
  Vector3 reflectionVector = (-lightVector + normal * 2 * normal.dot(lightVector)).normalize();

  double amountOfLightHittingPoint = lightVector.dot(normal);
  double amountOfReflectionHittingCamera = reflectionVector.dot(view);

  Color diffuseColor(0, 0, 0);
  Color specularColor(0, 0, 0);

  if (amountOfLightHittingPoint > 0) {
    diffuseColor = color * amountOfLightHittingPoint;

    if (amountOfReflectionHittingCamera > 0) {
      specularColor = light.color * pow(reflectionVector.dot(view), 10);
    }
  }

  colorAtPoint += (diffuseColor + specularColor) * lightIntensityAtPoint;

  return colorAtPoint;
}

Object::Object(float r, float g, float b, float specularity, float indexOfRefraction)
    : color(r, g, b), specularity(specularity), indexOfRefraction(indexOfRefraction) {

}
