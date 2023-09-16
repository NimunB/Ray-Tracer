// Termm--Fall 2020

#include <glm/ext.hpp>

#include "final.hpp"
#include "Ray.hpp"
#include "HitRecord.hpp"
#include "PhongMaterial.hpp"

#include <random>

using namespace std;
using namespace glm;

static const float Fudge = 0.0001;

const int ANTIALIASING_FACTOR = 1;
const bool MIRROR_REFLECTIONS = true;

const bool GLOSSY_REFLECTION_RAYS = 30;

static std::random_device rd;
//static default_random_engine mt(rd());
static std::mt19937 mt(rd());
static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

void printVecF(vec3 v, string name) {
    cout << name << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
}

Ray getGlossRay(const Ray & ray, const float glossiness) {
	const vec3 direction = ray.direction;
    const vec3 w = normalize(direction);
    const vec3 w_abs = vec3(fabs(w.x), fabs(w.y), fabs(w.z));
    
    vec3 t;
    if (w_abs.x <= w_abs.y && w_abs.x <= w_abs.z) {
        t = vec3(1.0f, w.y, w.z);
    } else if (w_abs.y <= w_abs.x && w_abs.y <= w_abs.z) {
        t = vec3(w.x, 1.0f, w.z);
    } else {
        t = vec3(w.x, w.y, 1.0f);
    }

    const vec3 u = normalize(cross(t, w));
    const vec3 v = cross(w, u);

    const float i = -glossiness / 2.0f + dist(mt) * glossiness;
    const float j = -glossiness / 2.0f + dist(mt) * glossiness;

    const vec3 glossy_direction = ray.direction + i * u + j * v;

    return Ray(ray.origin, glossy_direction);
}

vec3 rayColor(Ray & ray, SceneNode * root, const glm::vec3 & eye, const glm::vec3 & ambient, const std::list<Light *> & lights, const int maxHits = 7, bool fudgeOtherWay = false) {

	// Passed in to hit check
	HitRecord record;								
	// ray-object intersections
	if (root->hit(ray, 0, numeric_limits<double>::max(), record)) {		
										
		// Get surface intersection values
		record.normal = normalize(record.normal); // only normalizing once to minimize error
		if (fudgeOtherWay) {
			record.hit_point -= record.normal * Fudge;
		}
		else {
			record.hit_point += record.normal * Fudge; // You need to add a fudge factor or relocate the intersection point outside of the primitive, i.e., in the direction of the normal, by a small amount.
		}
		PhongMaterial * material = static_cast<PhongMaterial *>(record.material);
		vec3 color;
		vec3 spec = vec3(1.0, 1.0, 1.0);
		// Evaluate Blinn-Phong Shading model and set pixel to that color
			if(material->m_textured) {
				color = material->m_texture->getColor(record.u, record.v) * ambient;
			}
			// Color initialization - ambient lighting: surface color * ambient color. From https://learning-oreilly-com.proxy.lib.uwaterloo.ca/library/view/fundamentals-of-computer/9781482229417/K22616_C004.xhtml#sec4-5-3
			else {
				color = material->diffuse() * ambient;  
			}

			for (Light * light : lights) {
				// Create shadow ray from intersection point to each light source
				Ray shadowRay(record.hit_point, light->position - record.hit_point);
				HitRecord ShadowHit;

				if (material->m_textured || (material->diffuse() != vec3(0.0, 0.0, 0.0))) {
					// If object intersected by shadow ray, skip -> do not color obj
					if (root->hit(shadowRay, 0, numeric_limits<float>::max(), ShadowHit)) {
						continue;
					}
				}
				// Storing shading model values
				vec3 v = normalize(eye - record.hit_point); 
				vec3 l = normalize(shadowRay.direction);
				vec3 n = record.normal;
				vec3 r = normalize(- l + (2 * dot(l, n) * n)); // not needed for Blinn. For basic Phong
				vec3 h = (v + l)/length(v + l);
				float p = material->shininess();

				// diffuse
				vec3 diffuseComponent;
				if(material->m_textured) {
					diffuseComponent = material->m_texture->getColor(record.u, record.v);
				}
				else {
					diffuseComponent = material->diffuse();
				}
				if (material->m_textured || (material->diffuse() != vec3(0.0, 0.0, 0.0))) { // useless
					color += diffuseComponent * light->colour * glm::max(0.0, (double)dot(n, l)); // Textbook - Fundamentals of Computer Graphics. Marschner, Steve, author.; Shirley, Peter, author. 2018
				}

				// specular
				color += pow(glm::max(0.0, (double)dot(r, v)), p) * material->specular() * light->colour; // Textbook - Fundamentals of Computer Graphics. Marschner, Steve, author.; Shirley, Peter, author. 2018
			}
			vec3 reflectanceColor = vec3(0.0, 0.0, 0.0);
			vec3 refractanceColor = vec3(0.0, 0.0, 0.0);
			double fresnelCoef = 1.0;

			if (MIRROR_REFLECTIONS && material->shininess() > 0) {
				// Sending Mirror Reflection Rays
				if ((maxHits > 0) && (material->shininess() > 0)) { // need the shininess > 0 ?
					vec3 reflectDir = ray.direction - 2 * record.normal * dot(ray.direction, record.normal); // Law of reflection - need to check
					Ray reflectedRay(record.hit_point, reflectDir);
					if (material->isMirror() && (material->glossiness() > 0)) {
						//cout << "HI, I'M IN GLOSSY REFLECTION CODE" << endl;
						int numSamRays = GLOSSY_REFLECTION_RAYS;
						while (numSamRays > 0) {
							Ray glossRay = getGlossRay(reflectedRay, material->glossiness());
							reflectanceColor += (material->specular() * rayColor(glossRay, root, eye, ambient, lights, maxHits - 1));
							numSamRays--;
						}
						reflectanceColor /= GLOSSY_REFLECTION_RAYS;
					}
					else {
						reflectanceColor = (material->specular() * rayColor(reflectedRay, root, eye, ambient, lights, maxHits - 1));
					}
				}

				// Sending Refractance Rays 
				if ((maxHits > 0) && (material->refractance() > 0)) { 
				//if (false) {
					double cosI = dot(ray.direction, record.normal); // 9
					double nt = material->refractance();
					double ni = 1.0;
					vec3 ref_n = record.normal;
					if (cosI < 0.0) {
						// outside surface
						cosI = -cosI;
					}
					else {
						// inside surface
						ni = material->refractance();
						nt = 1.0;
						ref_n = -record.normal;
					}
					double nr = ni/nt;
					double cosR = 1.0 - (nr * nr) * (1.0 - (cosI * cosI));
					// No total internal reflection
					if (cosR >= 0) {
						// Computing Fresnel Coefficient
						cosR = sqrt(cosR);
						double firstPart = (ni * cosI - nt * cosR) / (ni * cosI + nt * cosR);
						double secondPart = (nt * cosI - ni * cosR) / (nt * cosI + ni * cosR);
						fresnelCoef = ((firstPart * firstPart) + (secondPart * secondPart)) / 2.0;
						// ------
						// ------ 
						vec3 refractDir = (ray.direction + cosI * ref_n) * nr - ref_n * cosR;
						Ray refractedRay(record.hit_point, refractDir);
						refractanceColor = material->specular() * rayColor(refractedRay, root, eye, ambient, lights, maxHits - 1, true);
						cout << "fresnel coef is: " << fresnelCoef << endl;
					}
				}
				else {
					fresnelCoef = 0.6;	// if no refraction
				}
				// Fresnel equation
				/*if (material->isMirror) {
					color = glm::mix(color, reflectanceColor, fresnelCoef);
				}*/
				//else {
				if (fresnelCoef == 0) fresnelCoef = 0.6;
				
				color += ((fresnelCoef * reflectanceColor) + ((1 - fresnelCoef) * refractanceColor));
					//color = glm::mix(color, reflectanceColor, fresnelCoef);
				//}
			}
			return color;
	}
	else {
		vec3 Background;
		vec3 dir = glm::normalize(ray.direction);
		float y = dir.y;
		float x = dir.x;
		Background = vec3(1.5 * y, 0.0, 1.0 * x);
		//Background = vec3(0,0,0); // 1.0*x
		return Background; // background color
	}

}
	

void final_Render(
		// What to render  
		SceneNode * root,

		// Image to write to, set to a given width and height  
		Image & image,

		// Viewing parameters  
		const glm::vec3 & eye, // lookFrom
		const glm::vec3 & view, // lookAr
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters  
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
) {

  // Fill in raytracing code here...  
  
  std::cout << "F20: Calling final_Render(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}
	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	size_t h = image.height();
	size_t w = image.width();
	// ---------------------------
	// Normalize vectors (beforehand, to minimize cost)
	vec3 n_w = normalize(view); 			// z-axis
	vec3 n_u = normalize(cross(n_w, up)); 	// x-axis
	vec3 n_v = cross(n_u, n_w); 			// y-axis
	// Finding d
	float d = h / 2 / tan(radians(fovy / 2));	// focal length
	// Defining image dimensions
	float l = w/2;
	float r = -l;
	float t = h/2;
	float b = -t;
	vec3 bottomLeft = (n_w * d) - (n_u * l) - (n_v * t);
	
	// For each pixel
	for (uint x = 0; x < w; x++) {
		for (uint y = 0; y < h; y++) {
			vec3 color = vec3(0.0, 0.0, 0.0); 
			for (int p = 0; p < ANTIALIASING_FACTOR; p++) {
				for (int q = 0; q < ANTIALIASING_FACTOR; q++) {
					
					float ssX = x + (p + 0.5)/ANTIALIASING_FACTOR;
					float ssY = y + (q + 0.5)/ANTIALIASING_FACTOR;

					// compute viewing ray
					float u = l + (r - l) * ssX/w;
					float v = b + (t - b) * ssY/h;
					//const vec3 direction = ((-1) * d * n_w) + (u * n_u) + (v * n_v);
					const vec3 direction = bottomLeft + ((h - ssY) * n_v) + (ssX * n_u); // Why must this happen?
					Ray ray = Ray(eye, direction);

					// compute intersections and pixel color
					color += rayColor(ray, root, eye, ambient, lights);
				}
			}
			color /= (ANTIALIASING_FACTOR * ANTIALIASING_FACTOR);
			// Red: 
			image(x, y, 0) = (double)color.r; //(double)1.0;
			// Green: 
			image(x, y, 1) = (double)color.g; //(double)1.0;
			// Blue: 
			image(x, y, 2) = (double)color.b;//(double)1.0;
		}
	}
	// ---------------------------
}
