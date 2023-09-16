# CS488 Final Project by Nimun Bajwa

Enhanced ray tracer in C++ that successfully simulates paths of light to create realistic rendering of 3D Lua scenes
Provided support for complex primitives, texture mapping, light reflection and refraction, transparent surfaces, and
shadows

### How to run:

1. Run "premake5 gmake" in ./final_proj
2. Run "make" in ./final_proj
3. Navigate to ./final_proj/Assets
4. Run ../final [lua scene]
    e.g. FINALSCENE.lua

### Objectives implemented:
- primitives
- anti aliasing
- texture mapping
- glossy reflection
- final scene
- refraction (sort of)

# CS 488 Ray Tracer Demo

## New Primitives
Cones, Cylinders, and Planes were added as new primitives to the modeling language. They were implemented by finding using their implicit equations in the intersection test.

![Sheet](demoPics/Primitives/sheet.png)
![Primitives](demoPics/Primitives/primitives.png)
![Floor](demoPics/Primitives/floor.png)

<div class="one-half column">
    <img class="u-max-full-width zoomImg" type="image/png" src="demoPics/Primitives/primitives.png"/>
    <img class="u-max-full-width zoomImg" type="image/png" src="demoPics/Primitives/sheet.png"/>
    <img class="u-max-full-width zoomImg" type="image/png" src="demoPics/Primitives/floor.png"/>
</div>

## Texture Mapping
Texture mapping was implmented for spheres, cylinders, cones, and planes. For spheres, spherical coordinates are used. Cones and cylinders both use cylindrical coordinates.

![Sphere Texture Mapping](demoPics/TextureMapping/sphereTM.png)
![Sheet Texture Mapping](demoPics/TextureMapping/sheetTM.png)
![Floor Texture Mapping](demoPics/TextureMapping/floorTM.png)
![Cylinder Texture Mapping](demoPics/TextureMapping/cylinderTM.png)
![Cone Texture Mapping](demoPics/TextureMapping/coneTM.png)


## Refraction
Refraction was implemented by calculating the refracted ray from Snell's law, and recursively sending these refraction rays. These rays contributed to the color decision using fresnel's coefficient. To prevent infinite recursion, there was a maximum depth limit to how many times a ray can be reflected or refracted.
![Refraction 1](demoPics/Refraction/floorRefraction.png)
![Refraction 2](demoPics/Refraction/refraction.png)
![Refraction 3](demoPics/Refraction/refractionOld.png)


## Glossy Reflection
Glossy reflection was implemented by adding glossiness to the gr.material command as a parameter. Multiple "glossy" reflection rays were then sent after perturbing their surface normals randomly.
![Glossy Reflection 2](demoPics/GlossyReflection/glossyReflection1.png)
![Glossy Reflection 1](demoPics/GlossyReflection/glossyReflection2.png)


## Anti-Aliasing
Anti-aliasing was implemented in the form of regular sampling. This was done by sampling multiple points within a given pixel, and averaging the color for the pixel.
![sphereTM2](demoPics/AntiAliasing/sphereTM2.png)
![sphereTM](demoPics/AntiAliasing/sphereTM.png)
![primitives2](demoPics/AntiAliasing/primitives2.png)
![primitives](demoPics/AntiAliasing/primitives.png)
![glossyReflection2](demoPics/AntiAliasing/glossyReflection2.png)
![glossyReflection](demoPics/AntiAliasing/glossyReflection1.png)

## Final Scene
Incorporates texture mapping, reflection, refraction, primitives, glossy reflection. Was meant to simulate an art gallery.
![FINALSCENE](demoPics/FinalScene/FINALSCENE.png)


## Extra Objective: Reflection
Note: This was my extra objective in A4.
Implemented by using Snell's law to calculate the reflected ray, and recursively incorporating that in the color calculation according to fresnel's coefficient.
![reflection](demoPics/Reflection/reflection.png)
![blueReflection](demoPics/Reflection/blueReflection.png)

