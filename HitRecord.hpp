#ifndef HitRecord_hpp
#define HitRecord_hpp

#include "Material.hpp"
#include <glm/glm.hpp>

using namespace glm;

class HitRecord {
public:
    double t;
    vec3 hit_point;
    vec3 normal;
    Material * material;
    float u;
    float v;
};

#endif