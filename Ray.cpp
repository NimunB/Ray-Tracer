

#include "Ray.hpp"

using namespace std;
using namespace glm;

Ray::Ray(const vec3 & origin, const vec3 & direction) : origin(origin), direction(direction) {}

vec3 Ray::At_t(double t) {
    return origin + (((float) t) * direction);
}