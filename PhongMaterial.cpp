// Termm--Fall 2020

#include "PhongMaterial.hpp"

using namespace glm;

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, double shininess, double refractance, double glossiness)
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
	, m_refractance(refractance)
	, m_textured(false)
	, m_glossiness(glossiness)
	, m_isMirror(false)
{}

PhongMaterial::PhongMaterial(Texture * texture, const glm::vec3& ks, double shininess, double refractance)
	: m_kd(vec3(0))
	, m_ks(ks)
	, m_shininess(shininess)
	, m_refractance(0.0f)
	, m_texture(texture)
	, m_textured(true)
	, m_glossiness(0.0f)
	, m_isMirror(false)
{}

PhongMaterial::PhongMaterial(
	const glm::vec3& kd, const glm::vec3& ks, double shininess, double refractance, double glossiness, bool isMirror)
	: m_kd(kd)
	, m_ks(ks)
	, m_shininess(shininess)
	, m_refractance(refractance)
	, m_textured(false)
	, m_glossiness(glossiness)
	, m_isMirror(isMirror)
{}

PhongMaterial::~PhongMaterial()
{}

glm::vec3 PhongMaterial::diffuse() {
	return m_kd;
}

glm::vec3 PhongMaterial::specular() {
	return m_ks;
}

double PhongMaterial::shininess() {
	return m_shininess;
}

double PhongMaterial::refractance() {
	return m_refractance;
}

double PhongMaterial::glossiness() {
	return m_glossiness;
}

bool PhongMaterial::isMirror() {
	return m_isMirror;
}