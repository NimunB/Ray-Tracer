// Termm--Fall 2020

#include "Primitive.hpp"
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace glm;

static const double EPSILON = 0.0001f;

Primitive::~Primitive()
{
}

bool Primitive::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    return false; // let it be
}

//--------------------------------------------------------------
Sphere::Sphere() {
    sphere = new NonhierSphere(vec3(0,0,0), 1);
}
Sphere::~Sphere()
{
    delete sphere;
}

bool Sphere::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    return sphere->hit(ray, tMin, tMax, record);
}
//--------------------------------------------------------------
Cube::Cube() {
    cube = new NonhierBox(vec3(0,0,0), 1);
}

Cube::~Cube()
{
    delete cube;
}

bool Cube::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    return cube->hit(ray, tMin, tMax, record);
}
//--------------------------------------------------------------
// NonhierSheet
//  m_pos, m_length, m_width
NonhierSheet::~NonhierSheet()
{
}
void printVec(vec3 v, string name) {
    cout << name << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

// width - height
// length - base
bool NonhierSheet::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    vec3 bottomLeft = m_pos;
    vec3 topLeft(m_pos.x, m_pos.y + m_width, m_pos.z);
    vec3 bottomRight(m_pos.x + m_length, m_pos.y, m_pos.z);
    vec3 topRight(m_pos.x + m_length, m_pos.y + m_width, m_pos.z);
    vec3 baseVec = bottomRight - bottomLeft;
    vec3 heightVec = topLeft - bottomLeft;

    vec3 normal = cross(baseVec, heightVec);
    double denom = dot(normal, ray.direction);

    double minX = m_pos.x - m_length/2;
    double maxX = m_pos.x + m_length/2;
    double minY = m_pos.y - m_width/2;
    double maxY = m_pos.y + m_width/2;

    /*cout << "--------------------" << endl;
    printVec(bottomLeft, "bottomLeft");
    printVec(topLeft, "topLeft");
    printVec(bottomRight, "bottomRight");
    printVec(topRight, "topRight");
    printVec(baseVec, "baseVec");
    printVec(heightVec, "heightVec");
    printVec(normal, "normal");*/

    if (fabs(denom) < EPSILON) return false;

    double t = dot(normal, m_pos - ray.origin) / denom;

    if (t < 0) return false;
    if (t < tMin || t > tMax) return false;

    vec3 hitPoint = ray.At_t(t);

    if ((hitPoint.x < minX) || (hitPoint.x  > maxX) || (hitPoint.y < minY) || (hitPoint.y  > maxY)) {
        return false;
    }

    record.hit_point = hitPoint;
    //printVec(record.hit_point, "hitPoint");
    record.t = t;
    if (dot(ray.direction, normal) > 0) {
        normal = -normal;
    }
    record.normal = normal;
    record.u = (hitPoint.x + m_length/2)/m_length;
    record.v = (hitPoint.y + m_width/2)/m_width;
    return true;
}

//--------------------------------------------------------------

// NonhierDisk
//  m_pos(pos), m_radius(radius)
NonhierDisk::~NonhierDisk()
{
}

// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
bool NonhierDisk::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    //cout << "aaa" << endl;
    // Assume disk is flat
    vec3 n(0.0, 1.0, 0.0);
    vec3 rayD = normalize(ray.direction); // NORMALIZE

    // Intersect with plane
    double denom = dot(n, rayD);
    double numerator = -dot(n, ray.origin);

    if (fabs(denom) < EPSILON) { // ABS
        return false;
    }
    //cout << "bbb" << endl;
    // Intersection t
    double t = dot(n, m_pos - ray.origin) * (1/denom);
    //double t = numerator / denom;
    if (t < 0) {
        //cout << "ccc" << endl; // 208
        return false;
    }

    // Intersection point
    vec3 hitPoint = ray.At_t(t);

        cout << "Hitpoint at t: " << t << " " << "(" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")" << endl;
        
        // NOW CHECK HERE
        // Check if intersection point is within radius
        vec3 dif = hitPoint - m_pos;
        double dif2 = dot(dif, dif);
        double radius2 = m_radius * m_radius;
        //cout << "ddd" << endl;
        if (dif2 > radius2) {
            //cout << "eee" << endl; // 802
            return false;
        }
        //cout << "Hitpoint at t: " << t << " " << "(" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")" << endl;

        //cout << "fff" << endl;
        // Flip normal if necessary
        if (dot(ray.origin - m_pos, n) < 0) {
            //cout << "ggg" << endl;
            n = -n;
        }

        //cout << "hhh" << endl;
        // Setting record
        record.t = t;
        record.normal = n;
        record.hit_point = hitPoint;

        return true;
    
}
//--------------------------------------------------------------
// NonhierCylinder
//  m_pos(pos), m_radius(radius)
NonhierCylinder::~NonhierCylinder()
{
}
bool NonhierCylinder::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    double A = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double B = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
    double C = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;

    double roots[2];
    size_t numRoots = quadraticRoots(A, B, C, roots);

    bool retVal;

    if (numRoots == 0) {
        retVal = false;
    }
    else if (numRoots == 1) {
        double t = roots[0];
        double y = ray.origin.y + ray.direction.y * t; 

        if (y <= 1 && y >= -1) {
            record.t = roots[0];
            record.hit_point = ray.At_t(t); // at t
            record.normal = glm::normalize(vec3(record.hit_point.x, 0, record.hit_point.z)); // normalized and 4 things in vec
            retVal = true;
        }
        else {
            retVal = false;
        }
    }
    else if (numRoots == 2) {
        double t1 = roots[0];
        double t2 = roots[1];

        double y1 = ray.origin.y + ray.direction.y * t1;
        double y2 = ray.origin.y + ray.direction.y * t2;

        if (t1 > t2) {
			// Store earlier t and y in 1
			std::swap(t1, t2);
			std::swap(y1, y2);
		}

        if (y1 < -1) {
            if (y2 < -1) {
                retVal = false;
            }
            else {
                // hit bottom cap
                double th = t1 + (t2 - t1) * (y1 + 1) / (y1 - y2);
				if (th <= 0) {
					retVal = false;
                }
                else {
                    record.t = th;
                    record.normal = vec3(0.0f, -1.0f, 0.0f);
                    record.hit_point = ray.At_t(th);

                    record.u = 0.5f + atan2(record.hit_point.x, record.hit_point.z) / (2 * M_PI);
                    record.v = record.hit_point.y / 1 + 0.5f;
                    retVal = true;
                }
            }
        }
        else if (y1 >= -1 && y1 <= 1) {
            // Hits the cylinder
            if (t1 <= 0) {
                retVal = false;
            }
            else {
                record.t = t1;
                record.hit_point = ray.At_t(t1);
                record.normal = glm::normalize(vec3(record.hit_point.x, 0.0f, record.hit_point.z)); // normalized

                record.u = 0.5f + atan2(record.hit_point.x, record.hit_point.z) / (2 * M_PI);
                record.v = record.hit_point.y/1 + 0.5f;

                //record.u = (M_PI + atan2(record.hit_point.x, record.hit_point.z))/ pow((2 * M_PI), 1);
                //record.v = 1/2 * (1 + record.hit_point.y);

                retVal = true;
            }
        }
        else if (y1 > 1) {
            if (y2 > 1) {
                retVal = false;
            }
            else {
                // Hits top cap
                double th = t1 + (t2 - t1) * (y1 - 1) / (y1 - y2);
                if (th <= 0) {
					return false;
                }
                else {
                    record.t = th;
                    record.normal = vec3(0.0f, 1.0f, 0.0f);
                    record.hit_point = ray.At_t(th);

                    record.u = 0.5f + atan2(record.hit_point.x, record.hit_point.z) / (2 * M_PI);
                    record.v = record.hit_point.y / 1 + 0.5f;

                    retVal = true;
                }
            }
        }
    }
    if (record.t < tMin || record.t > tMax) retVal = false;

    if (retVal) {
        // Test if it's inside the cylinder.
        double x = ray.origin.x;
        double y = ray.origin.y;
        double z = ray.origin.z;
        
        if (dot(ray.origin, record.normal) < 0) { // IF DO POSITION MUST FIX
            // inside.
            record.normal = -record.normal;
        }

    }
    return retVal;
}

//--------------------------------------------------------------
// NonhierCone
//  m_pos(pos), m_radius(radius)
NonhierCone::~NonhierCone()
{
}
bool NonhierCone::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    double A = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - ray.direction.y * ray.direction.y;
	double B = 2 * (ray.origin.x * ray.direction.x + ray.origin.z * ray.direction.z - ray.origin.y * ray.direction.y);
	double C = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - ray.origin.y * ray.origin.y;

    double roots[2];
    size_t numRoots = quadraticRoots(A, B, C, roots);

    bool retVal;

    if (numRoots == 0) {
        retVal = false;
    }
    else if (numRoots == 1) {
        double t = roots[0];
        double y = ray.origin.y + ray.direction.y * t; 

        if (y <= 1 && y >= 0) {
            record.t = t;
            record.hit_point = ray.At_t(t); // at t

            double dotXZ = sqrt(record.hit_point.x * record.hit_point.x + record.hit_point.z * record.hit_point.z);
			vec3 xD {1.0, record.hit_point.x / dotXZ, 0.0};
			vec3 zD {0.0, record.hit_point.z / dotXZ, 1.0};
			vec3 normal = glm::cross(xD, zD);
			record.normal = vec3(glm::normalize(normal));

            retVal = true;
        }
        else {
            retVal = false;
        }
    }
    else if (numRoots == 2) {
        double t1 = roots[0];
        double t2 = roots[1];

        double y1 = ray.origin.y + ray.direction.y * t1;
        double y2 = ray.origin.y + ray.direction.y * t2;

        if (t1 > t2) {
			// Store earlier t and y in 1
			std::swap(t1, t2);
			std::swap(y1, y2);
		}

        if (y1 < 0) {
            if (y2 < 0) {
                // Invalid
                retVal = false;
            }
            else {
                // Check if second point is valid
                if (y2 <= 1 && y2 >= 0) {
                    if (t2 > 0) {
						record.t = t2;
						record.hit_point = ray.At_t(t2);

						double dotXZ = sqrt(record.hit_point.x * record.hit_point.x + record.hit_point.z * record.hit_point.z);
						vec3 xD {1.0, record.hit_point.x / dotXZ, 0.0};
						vec3 zD {0.0, record.hit_point.z / dotXZ, 1.0};
						vec3 normal = glm::cross(xD, zD);
						record.normal = vec3(glm::normalize(normal));

                        retVal = true;
                    }
                    else {
                        retVal = false;
                    }
                }
                else {
                    retVal = false;
                }
            }
        }
        else if (y1 >= 0 && y1 <= 1) {
            // Hits the cone's curved part
            if (t1 <= 0) {
                retVal = false;
            }
            else {
                record.t = t1;
                record.hit_point = ray.At_t(t1);

                double dotXZ = sqrt(record.hit_point.x * record.hit_point.x + record.hit_point.z * record.hit_point.z);
				vec3 xD {1.0, record.hit_point.x / dotXZ, 0.0};
				vec3 zD {0.0, record.hit_point.z / dotXZ, 1.0};
				vec3 normal = glm::cross(xD, zD);
				record.normal = vec3(glm::normalize(normal));

                retVal = true;
            }
        }
        else if (y1 > 1) {
            if (y2 > 1) {
                retVal = false;
            }
            else {
                if (y2 <= 1 && y2 >= 0) {
                    if (t2 > 0) {
                        double th = ( 1 - ray.origin.y ) / ray.direction.y;
						vec3 tempHit = ray.At_t(th);
                        if (th >= 0 && (tempHit.x <= 1 && tempHit.x >= -1) && (tempHit.z <= 1 && tempHit.z >= -1)) {
							record.t = th;
							record.normal = vec3(0.0, 1.0, 0.0);
                            record.hit_point = tempHit;

                            retVal = true;
                        }
                        else {
                            retVal = false;
                        }
                    }
                    else {
                        retVal = false;
                    }
                }
                else {
                    retVal = false;
                }
            }
        }
    }
    if (record.t < tMin || record.t > tMax) retVal = false;

    if (retVal) {
        // Test if it's inside the cylinder.
        double x = ray.origin.x;
        double y = ray.origin.y;
        double z = ray.origin.z;
        
        if (dot(ray.origin, record.normal) < 0) { // IF DO POSITION MUST FIX
            // inside.
            record.normal = -record.normal;
        }

        record.u = 0.5f + atan2(record.hit_point.x, record.hit_point.z) / (2 * M_PI);
        record.v = -record.hit_point.y / 1;
    }
    return retVal;
}

//--------------------------------------------------------------
//  m_pos(pos), m_radius(radius)

NonhierSphere::~NonhierSphere()
{
}

bool NonhierSphere::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    vec3 d = ray.direction; // direction
    vec3 c = m_pos;         // centre of sphere
    vec3 e = ray.origin;    // eye
    double r = m_radius;    // radius of sphere
    vec3 ecDif = e - c;     // e - c

    float A = dot(d, d);
    float B = 2 * dot(d, ecDif);
    float C = dot(ecDif, ecDif) - (r * r);
    
    double roots[2];
    size_t numRoots = quadraticRoots(A, B, C, roots);
    float t;

    // Finding t (at intersection)
    switch(numRoots) {
        case 0:
            return false;
            break;
        case 1:
            t = roots[0];
            break;
        case 2:
            t = glm::min(roots[0], roots[1]);           // picking first intersection point
            break;
        default:
            break;
    }

    // Out of bounds - double check : NECESSARY FOR SHADING. W/O IT ALL WAS A SHADOW
    if ( t <= tMin || t >= tMax ) return false;

    record.t = t;
    record.hit_point = ray.At_t(t);
    record.normal = normalize(record.hit_point - c);   // removing 2 * for lack of error build up
    record.u = 0.5f + atan2(-record.normal.z, record.normal.x) / (2 * M_PI);
    record.v = 0.5f - asin(record.normal.y) / M_PI;
    //record.v = (M_PI - acos(record.hit_point.z / abs(record.hit_point.x)))/M_PI;


    return true;
}

//--------------------------------------------------------------
// m_pos(pos), m_size(size)
NonhierBox::NonhierBox(const glm::vec3& pos, double size): m_pos(pos), m_size(size) {
    // mesh version
    vector<vec3> vertices(8);
    vertices[0] = m_pos + vec3(0.0, 0.0, 0.0);
    vertices[1] = m_pos + vec3(m_size, 0.0, 0.0);
    vertices[2] = m_pos + vec3(m_size, 0.0, m_size);
    vertices[3] = m_pos + vec3(0.0, 0.0, m_size);
    vertices[4] = m_pos + vec3(0.0, m_size, 0.0);
    vertices[5] = m_pos + vec3(m_size, m_size, 0.0);
    vertices[6] = m_pos + vec3(m_size, m_size, m_size);
    vertices[7] = m_pos + vec3(0.0, m_size, m_size);
    
    // 2 triangles per face
    vector<vec3> triangles = {
        vec3(0, 2, 3),
        vec3(0, 3, 7),
        vec3(0, 7, 4),
        vec3(6, 1, 5),
        vec3(0, 4, 5),
        vec3(0, 5, 1),
        vec3(6, 2, 1),
        vec3(6, 3, 2),
        vec3(6, 5, 4),
        vec3(6, 4, 7),
        vec3(6, 7, 3),
        vec3(0, 1, 2)
    };
    cubeMesh = new Mesh(vertices, triangles);
}

NonhierBox::~NonhierBox()
{
    delete cubeMesh;
}

// We recommend that you implement cubes as a collection of six planes, rather than representing them as a mesh.
// https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection.html
// But we're doing it as a mesh because I think it's easier
bool NonhierBox::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
    return cubeMesh->hit(ray, tMin, tMax, record);
}
//--------------------------------------------------------------
