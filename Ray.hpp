#ifndef Ray_hpp
#define Ray_hpp

#include <glm/glm.hpp>

using namespace glm;

class Ray {
    public:
        vec3 origin;
        vec3 direction;

        Ray(const vec3 & origin,const vec3 & direction);

        vec3 At_t(double t);
};

#endif