/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Raytracer.hpp"
#include "Vector3D.hpp"
#include <iostream>
#include "Matrix/Matrix.hpp"

int main()
{
    // Vector3D vect1{4, 6, 42};
    // Vector3D vect2{4, 4, 4};
    // Math::Matrix<3, 3> rot{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // std::cout << vect1 << std::endl;
    // std::cout << vect1.length() << std::endl;

    // std::cout << vect2.dot(vect1) << std::endl;
    // std::cout << (((vect1 + vect1) * vect2) / vect2) * 2 << std::endl;
    // std::cout << rot.matMul(vect1) << std::endl;

    // std::cout << vect1.normalized() << std::endl;
    RayTracer::Flat yellow(Math::RGBA(255, 255, 0));
    RayTracer::Flat red(Math::RGBA(255, 0, 0));
    RayTracer::Flat blue(Math::RGBA(0, 0, 255));
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
