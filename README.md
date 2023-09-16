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
    <div>
        <p>Sheet</p>
        <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/sheet.png" alt="sheet" width="100%">
    </div>
    <div>
        <p>Primitives</p>
        <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/primitives.png" alt="primitives" width="100%">
    </div>
    <div>
        <p>Floor</p>
        <img src="https://raw.githubusercontent.com/NimunB/Ray-Tracer/main/demoPics/Primitives/floor.png" alt="floor" width="100%">
    </div>
</div>

## Texture Mapping
Texture mapping was implmented for spheres, cylinders, cones, and planes. For spheres, spherical coordinates are used. Cones and cylinders both use cylindrical coordinates.
![sphereTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/3c0c9f07-829d-4912-9408-be9b54a5d44d)
![sheetTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/471d40b2-ed3f-4b5d-bf09-96b7d74986bf)
![floorTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/cbe67196-858d-41fc-9f05-036e6f006378)
![cylinderTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/ae550cdf-5235-4cb9-9a13-263a7451bba2)
![coneTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/78561845-6e36-4c2f-88f4-d266538b291f)


## Refraction
Refraction was implemented by calculating the refracted ray from Snell's law, and recursively sending these refraction rays. These rays contributed to the color decision using fresnel's coefficient. To prevent infinite recursion, there was a maximum depth limit to how many times a ray can be reflected or refracted.
![refractionOld](https://github.com/NimunB/Ray-Tracer/assets/32827637/fc5e5ba2-3b69-48cd-a7a3-6406b55e878b)
![refraction](https://github.com/NimunB/Ray-Tracer/assets/32827637/6775ed2c-21d9-406b-bdc1-04c7cfee331d)
![floorRefraction](https://github.com/NimunB/Ray-Tracer/assets/32827637/0af14fe7-6b69-44d1-8977-5094386c3f00)


## Glossy Reflection
Glossy reflection was implemented by adding glossiness to the gr.material command as a parameter. Multiple "glossy" reflection rays were then sent after perturbing their surface normals randomly.
![glossyReflection2](https://github.com/NimunB/Ray-Tracer/assets/32827637/6dde9902-ebd2-4d87-bd7b-b392015bafed)
![glossyReflection1](https://github.com/NimunB/Ray-Tracer/assets/32827637/b43204b1-f2ac-422b-80e1-f142761a11aa)


## Anti-Aliasing
Anti-aliasing was implemented in the form of regular sampling. This was done by sampling multiple points within a given pixel, and averaging the color for the pixel.
![sphereTM2](https://github.com/NimunB/Ray-Tracer/assets/32827637/0a575cca-27f3-4f7e-a779-d99bf7ce7c64)
![sphereTM](https://github.com/NimunB/Ray-Tracer/assets/32827637/7ab34747-90b5-4a73-a419-436b26c64a96)
![primitives2](https://github.com/NimunB/Ray-Tracer/assets/32827637/6e9e7913-c21d-4b9f-9721-ba8e5816458f)
![primitives](https://github.com/NimunB/Ray-Tracer/assets/32827637/431f336b-8b41-464a-b0c1-c657aedf181f)
![glossyReflection2](https://github.com/NimunB/Ray-Tracer/assets/32827637/748ecf69-8511-4760-ad85-a81878c79d0f)
![glossyReflection](https://github.com/NimunB/Ray-Tracer/assets/32827637/a6bf1c17-5aec-47b0-950c-df168703bb2b)

## Final Scene
Incorporates texture mapping, reflection, refraction, primitives, glossy reflection. Was meant to simulate an art gallery.
![FINALSCENE](https://github.com/NimunB/Ray-Tracer/assets/32827637/7d3da585-e8de-4b07-915a-6dab254f37e2)


## Extra Objective: Reflection
Note: This was my extra objective in A4.
Implemented by using Snell's law to calculate the reflected ray, and recursively incorporating that in the color calculation according to fresnel's coefficient.
![reflection](https://github.com/NimunB/Ray-Tracer/assets/32827637/563df542-9317-4efd-9a55-b98eacbd129b)
![blueReflection](https://github.com/NimunB/Ray-Tracer/assets/32827637/24a2ec33-589a-4e6c-9f72-2afd5b990459)

