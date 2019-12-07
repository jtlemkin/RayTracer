//
// Created by James Lemkin on 12/6/19.
//

#ifndef HW5_PIXELBUFFER_H
#define HW5_PIXELBUFFER_H

#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <memory>
#include <algorithm>
#include "Color.h"

class PixelBuffer {
 private:
  size_t size;
  float* buffer;

  float maxIntensity;

  void updateMaxIntensity(float r, float g, float b);
 public:
  virtual ~PixelBuffer();
  explicit PixelBuffer(size_t size);

  void display();

  void recordPixel(int i, int j, const Color& color);

  void fill(float r, float g, float b);

  size_t getSize() const;
  void normalizePixels();
};

#endif //HW5_PIXELBUFFER_H
