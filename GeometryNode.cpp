// Termm--Fall 2020

#include "GeometryNode.hpp"

using namespace std;
//---------------------------------------------------------------------------------------
GeometryNode::GeometryNode(
	const std::string & name, Primitive *prim, Material *mat )
	: SceneNode( name )
	, m_material( mat )
	, m_primitive( prim )
{
	m_nodeType = NodeType::GeometryNode;
}

void GeometryNode::setMaterial( Material *mat )
{
	// Obviously, there's a potential memory leak here.  A good solution
	// would be to use some kind of reference counting, as in the 
	// C++ shared_ptr.  But I'm going to punt on that problem here.
	// Why?  Two reasons:
	// (a) In practice we expect the scene to be constructed exactly
	//     once.  There's no reason to believe that materials will be
	//     repeatedly overwritten in a GeometryNode.
	// (b) A ray tracer is a program in which you compute once, and 
	//     throw away all your data.  A memory leak won't build up and
	//     crash the program.

	m_material = mat;
}

// Each geometry node belongs to a primitive.
bool GeometryNode::hit(Ray & ray, double tMin, double tMax, HitRecord & record) {
	Ray transformedRay(vec3(invtrans * vec4(ray.origin, 1.0)), vec3(invtrans * vec4(ray.direction, 0.0)));

	HitRecord temp;
	double localMax = tMax;
	temp.material = nullptr; 
	bool hitResult = false;

	// Check if it hits primitive
	if (m_primitive->hit(transformedRay, tMin, tMax, temp)) {
		// If child does not have a material set, use parent's
		if ( temp.material == nullptr ) {
			temp.material = m_material; 
		}
		hitResult = true;
		localMax = temp.t;
		record = temp;	// hit record is set to what was hit
	}

	// HUH
	if ( SceneNode::hit(ray, tMin, localMax, temp) ) {
		hitResult = true;
		record = temp;
	}

	// Transforming normal and hitpoint back?
	if (hitResult) {
		record.normal = mat3(transpose(invtrans)) * record.normal;
		record.hit_point = vec3(trans * vec4(record.hit_point, 1.0));
	}

	// Returning hit result
	return hitResult;

}
