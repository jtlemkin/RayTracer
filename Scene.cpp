//
// Created by James Lemkin on 12/5/19.
//

#include "Scene.h"

Scene::Scene() : ambient(0, 0, 0) {}

void Scene::writeToBuffer(PixelBuffer &buffer) {
  size_t bufferSize = buffer.getSize();

  for (int i = 0; i < bufferSize; i++) {
    for (int j = 0; j < bufferSize; j++) {
      //Find the associated ray for each pixel
      Ray ray = camera.computeRayAt(i, j, (int) bufferSize - 1);

      Color pixColor = ambient + computeRayColor(ray);
      buffer.recordPixel(i, j, pixColor);
    }
  }
}

std::optional<Intersection> Scene::intersectRay(const Ray& ray) const {
  double closest = std::numeric_limits<double>::max();
  const Object* closestObject;
  int numIntersections;

  for (const auto &object : objects) {
    auto intersection = object->intersect(ray);

    if (intersection.has_value()) {
      Intersection _intersection = intersection.value();

      if (_intersection.t < closest and _intersection.t > 0.00001) {
        closest = _intersection.t;
        closestObject = &_intersection.object;
        numIntersections = _intersection.numIntersections;
      }
    }
  }

  if (closest != std::numeric_limits<double>::max()) {
    return Intersection(*closestObject, closest, numIntersections);
  } else {
    return {};
  }
}

void Scene::addSphere(double x, double y, double z, double radius, float r, float g, float b, float indexOfRefraction) {
  objects.push_back(std::make_unique<Sphere>(x, y, z, radius, r, g, b, 1, indexOfRefraction));
}
void Scene::setAmbientColor(float r, float g, float b) {
  ambient = Color(r, g, b);
}
void Scene::addLight(double x, double y, double z, float intensity, float r, float g, float b) {
  lights.emplace_back(x, y, z, intensity, r, g, b);
}
void Scene::addPlane(double A, double B, double C, double D, float r, float g, float b, float specularity,
                     float indexOfRefraction) {
  objects.push_back(std::make_unique<Plane>(A, B, C, D, r, g, b, specularity, indexOfRefraction));
}

Color computeDirectIllumination(Vector3 lightVector, Vector3 normal, Vector3 reflectionVector, Vector3 view,
                                Color objectColor, const Light& light) {
  //Todo: make k not hardcoded
  double lightIntensityAtPoint = light.intensity / (view.magnitude() + 0.5);

  double amountOfLightHittingPoint = lightVector.dot(normal);
  double amountOfReflectionHittingCamera = reflectionVector.dot(view);

  Color diffuseColor(0, 0, 0);
  Color specularColor(0, 0, 0);

  if (amountOfLightHittingPoint > 0) {
    diffuseColor = objectColor * amountOfLightHittingPoint;

    if (amountOfReflectionHittingCamera > 0) {
      specularColor = light.color * pow(reflectionVector.dot(view), 10);
    }
  }

  return (diffuseColor + specularColor) * lightIntensityAtPoint;
}

Color Scene::computeRayColor(const Ray& ray, int level) const {
  Color rayColor(0, 0, 0);

  //Compute closest intersection with object in scene
  auto intersection = intersectRay(ray);

  //Try next pixel if no intersection
  if (intersection.has_value() and level < 4) {
    const Object &intersectedObj = intersection.value().object;
    double t = intersection.value().t;

    Vector3 intersectionPoint = ray.getPointAt(t);

    //Compute light independent vectors
    Vector3 normal = intersectedObj.computeNormalAt(intersectionPoint);
    Vector3 view = (camera.getFromPoint() - intersectionPoint).normalize();

    for (const auto &light: lights) {
      Vector3 lightVector = (light.pos - intersectionPoint).normalize();
      Vector3 reflectionVector = (-lightVector + normal * 2 * normal.dot(lightVector)).normalize();

      //Find path from point to light
      Ray shadowFeeler = Ray(intersectionPoint, lightVector);

      auto lightRayIntersection = intersectRay(shadowFeeler);

      bool isIlluminated;

      if (lightRayIntersection.has_value()) {
        isIlluminated = lightRayIntersection.value().object.indexOfRefraction != -1
            || (light.pos - intersectionPoint).magnitude() < lightRayIntersection.value().t;
      } else {
        isIlluminated = true;
      }

      if (isIlluminated) {
        //This check is to make sure that we don't double count the color of an object while it's leaving the object
        if (intersectedObj.indexOfRefraction == -1) {
          if (lightRayIntersection.has_value() && lightRayIntersection.value().numIntersections == 2) {
            rayColor += computeDirectIllumination(lightVector, normal, reflectionVector, view, intersectedObj.color, light) * 0.5;
          } else {
            rayColor += computeDirectIllumination(lightVector, normal, reflectionVector, view, intersectedObj.color, light);
          }
        }

        Vector3 reflVector = (-view + normal * (normal.dot(view) * 2)).normalize();
        Ray reflRay = Ray(intersectionPoint, reflVector);

        rayColor += computeRayColor(reflRay, level + 1) * 0.05;

        rayColor += computeRefractedColor(intersection.value(), ray, level, view, normal) * 0.5;
      }
    }

    return rayColor;
  }
}

Object &Scene::getLastObject() {
  return *objects.back();
}

Color Scene::computeRefractedColor(const Intersection& intersection, const Ray& ray, int level, const Vector3& view,
                                   const Vector3& normal) const {
  Color refractedColor(0, 0, 0);

  auto intersectionPoint = ray.getPointAt(intersection.t);

  if (intersection.object.indexOfRefraction != -1) {
    Vector3 horizontalVector = (-view + normal * normal.dot(view)).normalize();

    double transmissionAngle = asin(1 / intersection.object.indexOfRefraction * sin(view.angleWith(normal)));
    Vector3 transmissionVector = (horizontalVector * sin(transmissionAngle) - normal * cos(transmissionAngle)).normalize();
    Ray transmissionRay = Ray(intersectionPoint, transmissionVector);

    auto insideIntersection = intersection.object.intersect(transmissionRay);

    if (insideIntersection.has_value()) {
      Vector3 exitPoint = transmissionRay.getPointAt(insideIntersection.value().t);

      Vector3 insideNormal = -intersection.object.computeNormalAt(exitPoint);
      Vector3 insideHorizontal = (-transmissionVector + insideNormal * insideNormal.dot(transmissionVector)).normalize();

      double insideTransmissionAngle = asin(intersection.object.indexOfRefraction
                                                * sin(transmissionVector.angleWith(insideNormal)));

      Vector3 insideTransmissionVector = (insideHorizontal * sin(insideTransmissionAngle) - insideNormal
          * cos(insideTransmissionAngle)).normalize();

      Ray insideTransmissionRay = Ray(exitPoint, insideTransmissionVector);

      return computeRayColor(insideTransmissionRay, level + 1);
    } else {
      std::cout << "catastrophic error\n";
    }

    return Color(0, 0, 0);

    /*if (intersection.numIntersections == 1 && ray.mediumIndex == 1) {
      Ray transmissionRay = Ray(intersectionPoint, ray.direction);

      refractedColor = computeRayColor(transmissionRay, level + 1);
    } else if (intersection.numIntersections == 1 && ray.mediumIndex != 1 && ray.mediumIndex * sin(view.angleWith(normal)) <= 1) {
      Vector3 horizontalVector = (-view + normal * normal.dot(view)).normalize();

      double transmissionAngle = asin(ray.mediumIndex * sin(view.angleWith(normal)));
      Vector3 transmissionVector = (horizontalVector * sin(transmissionAngle) + normal * cos(transmissionAngle)).normalize();
      Ray transmissionRay = Ray(intersectionPoint, transmissionVector);
      transmissionRay.mediumIndex = 1;

      refractedColor += computeRayColor(transmissionRay, level + 1);
    } else if (intersection.numIntersections == 2) {
      Vector3 horizontalVector = (-view + normal * normal.dot(view)).normalize();

      double transmissionAngle = asin(1 / intersection.object.indexOfRefraction * sin(view.angleWith(normal)));
      Vector3 transmissionVector = (horizontalVector * sin(transmissionAngle) - normal * cos(transmissionAngle)).normalize();
      Ray transmissionRay = Ray(intersectionPoint, transmissionVector);
      transmissionRay.mediumIndex = intersection.object.indexOfRefraction;

      refractedColor = computeRayColor(transmissionRay, level + 1);
    }*/
  }

  return refractedColor;
}

