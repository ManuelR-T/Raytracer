/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "RayTracer/Raytracer.hpp"
#include "RayTracer/Materials/Material.hpp"
#include <iostream>

int main()
{
    RayTracer::Materials::Flat yellow(Math::RGBA(255, 255, 0));
    RayTracer::Materials::Flat red(Math::RGBA(255, 0, 0));
    RayTracer::Materials::Flat blue(Math::RGBA(0, 0, 255));
    RayTracer::Scene scene(800, 600);
    scene.setCamera(RayTracer::Camera());

    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(0.1, 0, -1), 0.5, yellow));
    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(0, 0, -1), 0.5, red));
    scene.addShape(std::make_unique<RayTracer::Sphere>
        (Math::Point3D(1, 0, -1.5), 0.5, blue));

    scene.generateImage(std::cout);

    return 0;
}
