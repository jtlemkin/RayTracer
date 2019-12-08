//
// Created by James Lemkin on 12/6/19.
//

#include "Light.h"
Light::Light(double x, double y, double z, float intensity, float r, float g, float b) : pos(Vector3(x, y, z)),
                                                                                         intensity(intensity),
                                                                                         color(Color(r, g, b)) {}
