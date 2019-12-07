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

class PixelBuffer {
 private:
  size_t size;
  float* buffer;
 public:
  virtual ~PixelBuffer();
  PixelBuffer(size_t size);

  void display() const;

  void recordPixel(int i, int j, float r, float g, float b);
  void fill(float r, float g, float b);

  size_t getSize() const;
};

#endif //HW5_PIXELBUFFER_H
