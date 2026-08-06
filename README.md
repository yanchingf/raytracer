# Ray Tracer

A modern C++ ray tracer implementing physically based rendering techniques, including materials, lighting, acceleration structures, and camera effects.

## Features

- Recursive ray tracing engine written in modern C++
- Support for the following material types:
  - Diffuse (Lambertian)
  - Metallic surfaces (with adjustable fuzz/roughness)
  - Dielectric materials (glass/refraction)
- Physically based rendering effects:
  - Reflections
  - Refraction (Snell's law + Schlick approximation for reflectance)
  - Anti-aliasing via multi-sample pixel averaging
  - Gamma-corrected output
- Bounding volume hierarchy (AABB tree) for efficient ray-object intersection
- Configurable camera (field of view, position, orientation) and scene generation

## Implementation Details

The renderer follows a modular object-oriented design:

- **Ray-object intersections:** An abstract `Hittable` interface allows different geometric primitives (spheres, and future primitives) to share a common intersection and bounding-box pipeline.
- **Materials:** Surface behavior is modeled through material-specific `scatter()` functions to simulate diffuse, reflective, and refractive light interactions.
- **BVH acceleration:** An axis-aligned bounding box (AABB) tree reduces the number of ray-object intersection tests required per ray, improving performance as scene complexity grows.
- **Monte Carlo sampling:** Multiple jittered rays per pixel are averaged for anti-aliasing, and recursive bounced rays simulate indirect lighting.

## Build Instructions

### Requirements

- A C++ compiler supporting C++17 or later (e.g. `g++`, MinGW on Windows)

### Build

```bash
git clone https://github.com/yanchingf/raytracer.git
cd raytracer

g++ src/main.cpp -o main
```

## Running

After building, run the executable and redirect output to a `.ppm` image file:

```bash
./main > image.ppm
```

Open `image.ppm` with an image viewer that supports the PPM format (or convert it to PNG) to view the rendered scene. Scene contents and camera settings are currently configured directly in `main.cpp`.

## Project Structure

```
raytracer/
├── src/
│   ├── utilities/
│   │   ├── vec3.h           # 3D vector math, random sampling helpers
│   │   ├── ray.h            # Ray representation
│   │   ├── color.h          # Color output / PPM writing
│   │   ├── interval.h       # Reusable [min, max] range utility
│   │   ├── aabb.h           # Axis-aligned bounding box + ray-slab test
│   │   ├── hittable.h       # Hittable interface + Hit_Record
│   │   ├── hittable_list.h  # Flat list of hittable objects
│   │   ├── material.h       # Material interface + Lambertian/Metal/Dielectric
│   │   ├── sphere.h         # Sphere primitive
│   │   ├── bvh.h            # BVH node for spatial acceleration
│   │   └── camera.h         # Camera setup, ray generation, render loop
│   └── main.cpp             # Scene setup and entry point
└── README.md
```

## Future Improvements

Potential extensions:

- Multithreaded rendering
- Texture mapping (checker, image-based, procedural)
- Additional geometric primitives (triangles/meshes, quads)
- CMake build system for cross-platform builds
- GPU acceleration using CUDA
- More advanced global illumination techniques (importance sampling, light PDFs)

## References

Inspired by:

- *Ray Tracing in One Weekend* by Peter Shirley
- *Physically Based Rendering: From Theory to Implementation*

## Example Output

As of 7/29/26
![Rendered scene](docs/C:\Users\milan\Desktop\raytracer\docs\Screenshot 2026-08-02 202452.png)
