// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>

#include "Image.hpp"

using namespace std;

class Texture {
  public:
    virtual ~Texture();
    virtual glm::vec3 getColor(float u, float v) = 0;
};

class ImageTexture : public Texture {
  public:
    ImageTexture(const std::string & fileName, float widthFactor, float heightFactor);
    virtual ~ImageTexture();
    glm::vec3 getColor(float u, float v) override;
  private:
    Image image;
    float widthFactor;
    float heightFactor;
};
