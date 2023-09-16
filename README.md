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

<div style="display: flex; justify-content: space-between;">
    <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/primitives.png" alt="primitives" width="30%">
    <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/sheet.png" alt="sheet" width="30%">
    <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/floor.png" alt="floor" width="30%">
</div>

## Texture Mapping
Texture mapping was implmented for spheres, cylinders, cones, and planes. For spheres, spherical coordinates are used. Cones and cylinders both use cylindrical coordinates.
![sphereTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/563039d9-f52c-4158-8171-efc2c45db35a)
![sheetTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/9c8cd00e-d287-44b0-bcf9-dfedc9a6c1b1)
![floorTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/ae726e17-97c3-4267-a30f-5faa5927c3fa)
![cylinderTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/dd3fdb44-5955-44db-9e3e-1919746bcb83)
![coneTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/6d70ff1f-dbdd-474e-bc5c-af0389cec0b7)


## Refraction
Refraction was implemented by calculating the refracted ray from Snell's law, and recursively sending these refraction rays. These rays contributed to the color decision using fresnel's coefficient. To prevent infinite recursion, there was a maximum depth limit to how many times a ray can be reflected or refracted.

## Glossy Reflection
Glossy reflection was implemented by adding glossiness to the gr.material command as a parameter. Multiple "glossy" reflection rays were then sent after perturbing their surface normals randomly.

## Anti-Aliasing
Anti-aliasing was implemented in the form of regular sampling. This was done by sampling multiple points within a given pixel, and averaging the color for the pixel.

## Final Scene
Incorporates texture mapping, reflection, refraction, primitives, glossy reflection. Was meant to simulate an art gallery.

## Extra Objective: Reflection
Note: This was my extra objective in A4.
Implemented by using Snell's law to calculate the reflected ray, and recursively incorporating that in the color calculation according to fresnel's coefficient.
