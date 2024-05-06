/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Materials/Glassy.hpp"
#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "define.hpp"

#include "Materials/Materials.hpp"
#include "Transformations/Transformation.hpp"
#include "Shapes/Shapes.hpp"

#include <exception>
#include <iostream>
#include <cmath>

int main(int ac, char **av)
{
    if (ac != 2)
        return FAILURE;
    try {
        RayTracer::SceneParser::parseScene(av[1]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return FAILURE;
    }
    // RayTracer::Flat yellow(Math::RGBA(255, 255, 0));
    // RayTracer::Flat red(Math::RGBA(255, 0, 0));
    // RayTracer::Glassy blue(Math::RGBA(0, 0, 255));
    // RayTracer::Flat green(Math::RGBA(0, 255, 0));
    // RayTracer::Scene scene(800, 600);

    // RayTracer::Scene scene(800, 600);
    // Vector3D pt{0.1, 0, -1};
    // Vector3D t{-0.5, 0, 0};
    // scene.setCamera(RayTracer::Camera(Point3D{0, 0, 1}));

    // scene.addLight(std::make_unique<RayTracer::PointLight>
    //      (Point3D{0, -1, 1}, Math::RGBA(0, 255, 255)));
    // scene.addLight(std::make_unique<RayTracer::PointLight>
    //      (Point3D{1, -1, 1}, Math::RGBA(200, 0, 0)));

    // scene.addShape(std::make_unique<RayTracer::Sphere>
    //     (Point3D{0.5, 0, -1}, 0.4, red));
    // scene.addShape(std::make_unique<RayTracer::Sphere>
    //     (Point3D{-0.5, 0, -1}, 0.4, blue));
    // scene.addShape(std::make_unique<RayTracer::Plane>
    //     (Point3D{0, -1, 0}, Vector3D{0, 1, 0}, green));

    // scene.generateImage(std::cout);
    return SUCCESS;
}
