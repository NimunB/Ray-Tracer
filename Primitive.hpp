// Termm--Fall 2020

#pragma once

#include <glm/glm.hpp>
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "polyroots.hpp"
#include <cmath>

class Mesh;
class Primitive {
public:
  virtual ~Primitive();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record);
};

class Sphere : public Primitive {
  Primitive * sphere;
public:
  Sphere();
  virtual ~Sphere();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;
};

class Cube : public Primitive {
  Primitive * cube;
public:
  Cube();
  virtual ~Cube();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;
};

class NonhierCylinder : public Primitive {
public:
  NonhierCylinder(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierCylinder();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierCone : public Primitive {
public:
  NonhierCone(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierCone();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierDisk : public Primitive {
public:
  NonhierDisk(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierDisk();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_radius;
};

class NonhierSheet : public Primitive {
public:
  NonhierSheet(const glm::vec3& pos, double length, double width)
    : m_pos(pos), m_length(length), m_width(width)
  {
  }
  virtual ~NonhierSheet();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_length;
  double m_width;
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_radius;
  
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size);
  virtual ~NonhierBox();
  virtual bool hit(Ray & ray, float tMin, float tMax, HitRecord & record) override;

private:
  glm::vec3 m_pos;
  double m_size;

  Primitive * cubeMesh;
};
