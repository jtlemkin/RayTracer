//
// Created by James Lemkin on 12/6/19.
//

#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(size_t size) : size(size), buffer(new float[size * size * 3]) {
}

void PixelBuffer::recordPixel(int i, int j, float r, float g, float b) {
  buffer[3 * (i + j * size)    ] = r;
  buffer[3 * (i + j * size) + 1] = g;
  buffer[3 * (i + j * size) + 2] = b;
}
void PixelBuffer::display() const {
  glDrawPixels(size, size, GL_RGB, GL_FLOAT, buffer);
}
PixelBuffer::~PixelBuffer() {
  delete [] buffer;
}
void PixelBuffer::fill(float r, float g, float b) {
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      recordPixel(i, j, r, g, b);
    }
  }
}
size_t PixelBuffer::getSize() const {
  return size;
}
