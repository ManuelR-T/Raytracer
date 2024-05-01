/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Scene.hpp"

#include "Materials/Materials.hpp"
#include "Transformations/Transformation.hpp"
#include "Shapes/Shapes.hpp"

#include <iostream>
#include <cmath>

int main()
{
    RayTracer::Flat yellow(Math::RGBA(255, 255, 0));
    RayTracer::Flat red(Math::RGBA(255, 0, 0));
    RayTracer::Flat blue(Math::RGBA(0, 0, 255));
    RayTracer::Scene scene(800, 600);
    Vector3D pt{0.1, 0, -1};
    Vector3D t{-0.5, 0, 0};


    scene.setCamera(RayTracer::Camera());
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(pt.normalized(), 0.5, yellow));
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(Point3D{0, 0, -1}, 0.5, red));
    scene.addShape(
        std::make_unique<RayTracer::Sphere>(Point3D{1, 0, -1.5}, 0.5, blue));
    scene.generateImage(std::cout);
    return 0;
}
