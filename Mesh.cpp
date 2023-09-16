// Termm--Fall 2020

#include <iostream>
#include <fstream>

#include <glm/ext.hpp>
#include "Primitive.hpp"
#include <glm/glm.hpp>
// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"
using namespace glm;
using namespace std;

// Different from in class. (Easier method found online)
bool rayIntersectTriangle(Ray & ray, vec3 vertex0, vec3 vertex1, vec3 vertex2, float & res) {
	const float EPSILON = 0.0000001;
	vec3 edge1, edge2, h, s, q;
	float a, f, u, v;
	edge1 = vertex1 - vertex0;
	edge2 = vertex2 - vertex0; 

	h = cross(ray.direction, edge2);
	a = glm::dot(edge1, h);
	if (a > -EPSILON && a < EPSILON)
		return false;
	f = 1 / a;
	s = ray.origin - vertex0;
	u = f * dot(s, h);
	if (u < 0.0 || u > 1.0) {
		return false;
	}
	q = cross(s, edge1);
	v = f * dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0) {
		return false;
	}
	// Find t
	float t = f * dot(edge2, q);
	if (t > EPSILON) // ray intersection
	{
		res = t;
		return true;
	}
	else return false;
}


Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*
  
  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}

bool Mesh::hit(Ray & ray, float tMin, float tMax, HitRecord & record) {
	float higher = tMax;
	vec3 normal = vec3();
    bool hit = false;
	for ( auto triangle : m_faces ) {
        float tempT;
        if (rayIntersectTriangle(ray, m_vertices[triangle.v1], m_vertices[triangle.v2], m_vertices[triangle.v3], tempT) ) {
            if ( tempT < higher && tempT > tMin ) {
                hit = true;
                higher = tempT;
                normal = cross(m_vertices[triangle.v1] - m_vertices[triangle.v2], m_vertices[triangle.v2] - m_vertices[triangle.v3]);
            }
        }
    }
	if (!hit) return false;

	if (dot(ray.direction, normal) > 0) {
		normal = -normal;
	}

	record.t = higher;
	record.normal = normal;
	record.hit_point = ray.At_t(record.t);
	record.material = nullptr; // necessary?

	return hit;
}

// 2nd constructor
Mesh::Mesh(vector<vec3> & vertices, const vector<vec3> & faces) :
	m_vertices(vertices) {

	m_faces.resize(faces.size()); // necessary resize? yes
	for (size_t i = 0; i < faces.size(); i++) { // triangle for each face
		Triangle t((size_t)faces[i].x, (size_t)faces[i].y, (size_t)faces[i].z);
		//Triangle t(faces[i].x, faces[i].y, faces[i].z);
		m_faces[i] = t;
	}
}