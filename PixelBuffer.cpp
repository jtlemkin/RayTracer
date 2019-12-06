//
// Created by James Lemkin on 12/6/19.
//

#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(size_t width, size_t height) : width(width), height(height),
                                                        buffer(new float[width * height * 3]) {
}

void PixelBuffer::recordPixel(int i, int j, float r, float g, float b) {
  buffer[3 * (i + j * width)    ] = r;
  buffer[3 * (i + j * width) + 1] = g;
  buffer[3 * (i + j * width) + 2] = b;
}
void PixelBuffer::display() const {
  glDrawPixels(width, height, GL_RGB, GL_FLOAT, buffer);
}
PixelBuffer::~PixelBuffer() {
  delete [] buffer;
}
void PixelBuffer::fill(float r, float g, float b) {
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      recordPixel(i, j, r, g, b);
    }
  }
}
size_t PixelBuffer::getWidth() const {
  return width;
}
size_t PixelBuffer::getHeight() const {
  return height;
}
