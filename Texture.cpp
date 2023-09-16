// Termm--Fall 2020

#include <glm/glm.hpp>

#include "Texture.hpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace glm;

Texture::~Texture() {}

ImageTexture::ImageTexture(const string & filename, float widthFactor, float heightFactor) : widthFactor{widthFactor}, heightFactor{heightFactor} {
  cout << "Applying the " << filename << " texture to your image." << endl;
  image = Image::loadPng(filename);
}

ImageTexture::~ImageTexture() {}

vec3 ImageTexture::getColor(float u, float v) {
  // Use value of texture pixel closest to u,v as the texture value
  const uint tWidth = image.width();
  const uint tHeight = image.height();

  //const uint i = (uint)round(u * tWidth - 0.5);
  //const uint j = (uint)round(v * tHeight - 0.5);

  //const uint i = (uint)round(u * widthFactor - 0.5);
  //const uint j = (uint)round(v * heightFactor - 0.5);

  const uint i = (uint)round(u * widthFactor * tWidth) % tWidth;
  const uint j = (uint)round(v * heightFactor * tHeight) % tHeight;

  /*cout << "texture width: " << tWidth << endl;
  cout << "texture height: " << tHeight << endl;
  cout << "u: " << u << endl;
  cout << "v: " << v << endl;
  cout << "i: " << i << endl;
  cout << "j: " << j << endl;*/

  const double r = image(i, j, 0);
  const double g = image(i, j, 1);
  const double b = image(i, j, 2);

  //return vec3(0,0,0);
  return vec3(r, g, b);
}
