# Raytracer Project

[![Pipeline](https://github.com/ManuelR-T/Raytracer/actions/workflows/pipeline.yml/badge.svg)](https://github.com/ManuelR-T/Raytracer/actions/workflows/pipeline.yml)

## Overview

This project is a Raytracer, a program designed to render 3D scenes using ray tracing techniques. The project is implemented in C++ and uses SFML (Simple and Fast Multimedia Library) for graphical output.

## Features

- **3D Rendering**: The program takes a scene description file as input and renders the scene using ray tracing.
- **Modular Design**: The code is organized into several modules, including Parsing, Error Handling, Scene Management, Camera Handling, Transformations, and Shapes.
- **Configurable Options**: The raytracer can be customized using various options passed through a configuration file.
- **Error Handling**: The program includes robust error handling to manage exceptions and unexpected inputs.

## Requirements

- **C++20**: The project is written in C++ and requires a C++20 compliant compiler.
- **SFML**: The project uses the SFML library for graphical output. Ensure you have the `sfml-graphics`, `sfml-window`, and `sfml-system` libraries installed.
- **libconfig++**: The project uses `libconfig++` for handling configuration files.

## Compilation

To compile the project, use the provided Makefile. The Makefile defines several targets:

- `all`: Compiles the project and generates the executable.
- `debug`: Compiles the project with debugging information.
- `clean`: Removes all object files.
- `fclean`: Performs a `clean` and also removes the executable.
- `re`: Cleans and recompiles the project.

To compile the project, simply run:

```bash
make
```

This will produce an executable named `raytracer`.

For debugging purposes, you can compile the project with debug flags by running:

```bash
make debug
```

## Usage

Once compiled, you can run the raytracer by passing a scene file as an argument:

```bash
./raytracer scene.raytracer
```

- **scene.raytracer**: This is a text file that describes the scene to be rendered, including objects, lights, camera settings, and other parameters.

## Scene File Format

The scene file used by the raytracer is a structured text file that defines the various elements of a 3D scene, including the camera, primitives (geometric shapes), and lighting. The file uses a hierarchical structure, where each section defines specific properties of the scene. Below is an explanation of the format and its components:

### 1. Camera Configuration
The `camera` section defines the properties of the camera used to render the scene. It includes:

- **resolution**: Specifies the output image dimensions.
  - `width`: The width of the image in pixels.
  - `height`: The height of the image in pixels.

- **position**: The 3D coordinates of the camera's position in the scene.
  - `x`, `y`, `z`: Cartesian coordinates.

- **rotation**: Specifies the camera's rotation around the X, Y, and Z axes.
  - `x`, `y`, `z`: Rotation angles in degrees.

- **translation**: The camera's translation along the X, Y, and Z axes.
  - `x`, `y`, `z`: Translation values.

- **fieldOfView**: The camera's field of view in degrees.

```plaintext
camera :
{
    resolution = { width = 800; height = 600; };
    position = { x = 0.0; y = 0.0; z = 1.0; };
    rotation = { x = 0.0; y = 0.0; z = 0.0; };
    translation = { x = 0.0; y = 0.0; z = 0.0; };
    fieldOfView = 120;
};
```

### 2. Primitives
The `primitives` section lists the geometric shapes that make up the scene. Each type of primitive (spheres, planes, cones, cylinders, cubes) has its own subsection.

#### Spheres
Defines a list of spheres in the scene. Each sphere has:
- **x, y, z**: Position of the sphere's center.
- **r**: Radius of the sphere.
- **color**: Primary color of the sphere.
- **color2**: Secondary color (used in materials like "ChessBoard").
- **material**: The material type, such as "Glassy", "Flat", "Perlin", "ChessBoard".
- **translation**: Translation applied to the sphere.
- **scale**: Scale factor for the material.

```plaintext
spheres = (
    {
        x = 0.5;
        y = 0.0;
        z = -1.0;
        r = 0.4;
        color = { r = 255; g = 0; b = 0; };
        material = "Glassy";
        translation = { x = 0.0; y = 0.0; z = 0.0; };
        scale = 0.0025;
    }
);
```

#### Planes
Defines a list of planes in the scene. Each plane has:
- **axis**: A vector defining the plane's orientation.
- **position**: The position of the plane.
- **color**: Primary color of the plane.
- **color2**: Secondary color.
- **material**: The material type, such as "Glassy", "Flat", "Perlin", "ChessBoard".
- **scale**: Scale factor for the material.

```plaintext
planes = (
    {
        axis = { x = 0.0; y = 1.0; z = 0.0; };
        position = { x = 0.0; y = 1.0; z = 0.0; };
        color = { r = 255; g = 255; b = 255; };
        color2 = { r = 0; g = 0; b = 0; };
        material = "ChessBoard";
        scale = 0.1
    }
);
```

#### Cones
Defines a list of cones in the scene. Each cone has:
- **position**: Position of the cone's base center.
- **r**: Base radius of the cone.
- **axis**: Orientation of the cone's axis.
- **color**: Primary color.
- **color2**: Secondary color.
- **material**: The material type, such as "Glassy", "Flat", "Perlin", "ChessBoard".
- **scale**: Scale factor for the material.
- **translation**: Translation applied to the cone.
- **rotation**: Rotation applied to the cone.
- **height**: Height of the cone.

```plaintext
cones = (
    { 
        position = { x = -0.4; y = 1.0; z = -1.0; };
        r = 0.5;
        color = { r = 0; g = 0; b = 255; };
        axis = { x = 0.0; y = -1.0; z = 0.0 };
        material = "Perlin";
        scale = 0.01;
        translation = { x = 0.0; y = 0.0; z = 0.0; };
        rotation = { x = 0.0; y = 0.0; z = 0.0; };
        height = 1.0;
    }
);
```

#### Cylinders
Defines a list of cylinders. Each cylinder has:
- **position**: Position of the cylinder's base center.
- **r**: Radius of the cylinder.
- **color**: Primary color.
- **axis**: Orientation of the cylinder's axis.
- **color2**: Secondary color.
- **material**: The material type, such as "Glassy", "Flat", "Perlin", "ChessBoard".
- **scale**: Scale factor for the cylinder.
- **translation**: Translation applied to the cylinder.
- **rotation**: Rotation applied to the cylinder.
- **height**: Height of the cylinder.

```plaintext
cylinders = (
    {
        position = { x = 1.5; y = 0.0; z = -1.0; };
        r = 0.1;
        color = { r = 0; g = 0; b = 255; };
        axis = { x = 0.0; y = -1.0; z = 0.0 };
        material = "Perlin";
        scale = 0.01;
        translation = { x = 0.0; y = 0.0; z = 0.0; };
        rotation = { x = 0.0; y = 0.0; z = 0.0; };
        height = 0.5;
    }
);
```

#### Cubes
Defines a list of cubes in the scene. Each cube has:
- **position**: Position of the cube's center.
- **r**: Size of the cube (side length).
- **color**: Primary color.
- **color2**: Secondary color.
- **axis**: Orientation axis for rotations.
- **material**: The material type, such as "Glassy", "Flat", "Perlin", "ChessBoard".
- **scale**: Scale factor for the material.

```plaintext
cubes = (
    {
        position = {x = 1.4; y = -0.8; z = -2.0;};
        r = 1.0;
        color = { r = 255; b = 0; g = 0; };
        material = "Perlin";
        scale = 0.0025;}
);
```

### 3. Light Configuration
The `lights` section defines the lighting conditions in the scene.

#### Ambient and Diffuse Lighting
- **ambient**: Multiplier for ambient light.
- **diffuse**: Multiplier for diffuse light.

```plaintext
lights :
{
    ambient = 0.4;
    diffuse = 0.6;
};
```

#### Point Lights
Defines a list of point lights, each with:
- **x, y, z**: Position of the light source.
- **color**: Color of the light.

```plaintext
point = (
    { x = 0.0; y = 1.0; z = 1.0; color = { r = 255; g = 255; b = 255; }; }
);
```

#### Directional Lights
Defines a list of directional lights, each with:
- **x, y, z**: Direction vector of the light.
- **color**: Color of the light.

```plaintext
directional = (
    { x = 0.0; y = -1.0; z = 1.0; color = { r = 255; g = 255; b = 255; }; }
);
```
---

This format allows for a flexible and detailed description of the scene, which the raytracer will use to generate the final rendered image. Make sure to follow the format precisely to avoid any errors during rendering.


## Cleaning Up

To clean up the build directory and remove all compiled files, run:

```bash
make clean
```

To remove the compiled executable along with the object files, run:

```bash
make fclean
```

## Rebuilding

To clean and rebuild the entire project from scratch, run:

```bash
make re
```
