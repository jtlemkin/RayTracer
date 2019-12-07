//
// Created by James Lemkin on 12/6/19.
//

#include "PixelBuffer.h"

PixelBuffer::PixelBuffer(size_t size) : size(size), buffer(new float[size * size * 3]), maxIntensity(0) {
}

void PixelBuffer::recordPixel(int i, int j, const Color& color) {
  buffer[3 * (i + j * size)    ] = color.r;
  buffer[3 * (i + j * size) + 1] = color.g;
  buffer[3 * (i + j * size) + 2] = color.b;

  updateMaxIntensity(color.r, color.g, color.b);
}

void PixelBuffer::display() {
  normalizePixels();
  glDrawPixels(size, size, GL_RGB, GL_FLOAT, buffer);
}

PixelBuffer::~PixelBuffer() {
  delete [] buffer;
}

void PixelBuffer::fill(float r, float g, float b) {
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      Color color(r, g, b);
      recordPixel(i, j, color);
    }
  }
}

size_t PixelBuffer::getSize() const {
  return size;
}

void PixelBuffer::updateMaxIntensity(float r, float g, float b) {
  if (r > maxIntensity) {
    maxIntensity = r;
  }

  if (g > maxIntensity) {
    maxIntensity = g;
  }

  if (b > maxIntensity) {
    maxIntensity = b;
  }
}
void PixelBuffer::normalizePixels() {
  for(int i = 0; i < size * size * 3; i++) {
    buffer[i] /= maxIntensity;
  }
}
