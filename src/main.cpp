/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Materials/Glassy.hpp"
#include "Scene.hpp"

#include "Materials/Materials.hpp"
#include "Shapes/Cube.hpp"
#include "Transformations/Transformation.hpp"
#include "Shapes/Shapes.hpp"

#include <fstream>
#include <iostream>

int main() {
    RayTracer::Flat yellow(Math::RGBA(255, 255, 0));
    RayTracer::Flat red(Math::RGBA(255, 0, 0));
    RayTracer::Glassy blue(Math::RGBA(0, 0, 255));
    RayTracer::Flat green(Math::RGBA(0, 255, 0));

    RayTracer::Scene scene(800, 600, 120);
    Vector3D pt{0.1, 0, -1};
    Vector3D t{-0.5, 0, 0};
    std::ofstream file("image.ppm");

    scene.setCamera(RayTracer::Camera(Point3D{0, 0, 1}));

    // scene.addLight(std::make_unique<RayTracer::PointLight>
        //  (Point3D{0, -1, 1}, Math::RGBA(255, 255, 255)));
    scene.addLight(std::make_unique<RayTracer::PointLight>
         (Point3D{0, 1, 10}, Math::RGBA(255, 255, 255)));
    scene.addLight(std::make_unique<RayTracer::PointLight>
        (Point3D{-20, 1, -25}, Math::RGBA(255, 255, 255)));
    //scene.addLight(std::make_unique<RayTracer::DirectionalLight>
    //     (Vector3D{0, -1, 1}, Math::RGBA(255, 255, 255)));

    // scene.addShape(std::make_unique<RayTracer::Sphere>
        // (Point3D{0.5, 0, -1}, 0.4, red));
    scene.addShape(std::make_unique<RayTracer::Cones>
        (Point3D{0.5, 1, -1.5}, blue, 0.3, Vector3D{0, -1, 0}));
    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Point3D{-0.5, -0.5, -1}, 0.4, blue));
    scene.addShape(std::make_unique<RayTracer::Plane>
        (Point3D{0, 1, 0}, Vector3D{0, 1, 0}, green));
    scene.addShape(std::make_unique<RayTracer::Cube>
        (Point3D{1.4, -0.5, -1}, 0.5, red));

    scene.generateImage(file);
    return 0;
}
