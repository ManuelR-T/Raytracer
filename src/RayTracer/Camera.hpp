/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#pragma once

#include "Ray.hpp"
#include "IObject.hpp"

#include <memory>
#include <vector>

namespace RayTracer {
class Camera {
public:
    Math::Point3D origin;

    Camera(const Math::Point3D &origin = Math::Point3D(0, 0, 1));
    Ray ray(double u, double v) const;
    Math::RGBA
    traceRay(const Ray &ray,
             const std::vector<std::unique_ptr<IObject>> &shapes) const;

private:
    Math::RGBA defaultColor{0, 0, 0};
};
}