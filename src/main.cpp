/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Raytracer.hpp"
#include "Vector3D.hpp"
#include <iostream>

int main()
{

    RayTracer::Scene scene(800, 600);
    scene.setCamera(RayTracer::Camera());

    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(0.1, 0, -1), 0.5, Math::RGBA(255, 255, 0)));
    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(0, 0, -1), 0.5, Math::RGBA(255, 0, 0)));
    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(1, 0, -1.5), 0.5, Math::RGBA(0, 255, 0)));

    scene.generateImage(std::cout);

    return 0;
}
