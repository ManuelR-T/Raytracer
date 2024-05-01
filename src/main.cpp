/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"

#include "Materials/Materials.hpp"
#include "Shapes/Shapes.hpp"

#include <iostream>

int main()
{
    RayTracer::Flat yellow(Math::RGBA(255, 255, 0));
    RayTracer::Flat red(Math::RGBA(255, 0, 0));
    RayTracer::Flat blue(Math::RGBA(0, 0, 255));
    RayTracer::Flat green(Math::RGBA(0, 255, 0));
    RayTracer::Scene scene(800, 600);

    scene.setCamera(RayTracer::Camera());
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(Point3D{0.1, 0, -1}, 0.5, yellow));
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(Point3D{0, 0, -1}, 0.5, red));
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(Point3D{1, 0, -1.5}, 0.5, blue));
    scene.addShape(
        std::make_unique<RayTracer::Plane>(Point3D{0, -1, 0}, Vector3D{0, 1, 0}, green));
    scene.generateImage(std::cout);
    return 0;
}
