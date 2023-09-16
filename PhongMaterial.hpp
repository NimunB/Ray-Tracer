// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>

#include "Material.hpp"
#include "Texture.hpp"

class PhongMaterial : public Material {
public:
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess, double refractance, double glossiness);
  PhongMaterial(Texture * texture, const glm::vec3& ks, double shininess, double refractance);
  PhongMaterial(const glm::vec3& kd, const glm::vec3& ks, double shininess, double refractance, double glossiness, bool isMirror);

  virtual ~PhongMaterial();
  glm::vec3 diffuse();
  glm::vec3 specular();
  double shininess();
  double refractance();
  double glossiness();
  bool isMirror();

  bool m_textured;
  Texture * m_texture;

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;

  double m_shininess;
  double m_refractance;

  double m_glossiness;

  bool m_isMirror;
};
