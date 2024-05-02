/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"

namespace RayTracer {
class Scene;
class Camera {
public:
    Point3D origin;

    Camera(const Point3D &origin = Point3D{0.f, 0.f, 1.f});

    Ray ray(double u, double v) const;
    Math::RGBA traceRay(const Ray &ray, const Scene &scene) const;

private:
    Math::RGBA defaultColor{0, 0, 0};
};

} // namespace RayTracer