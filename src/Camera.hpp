/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#pragma once

#include "Shapes/IShape.hpp"
#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include "Raytracer.hpp"

#include <memory>

namespace RayTracer {
class Camera {
public:
    Point3D origin;

    Camera(const Point3D &origin = Point3D{0.f, 0.f, 1.f}) : origin(origin)
    {
    }

    Ray ray(double u, double v) const
    {
        return Ray(origin, Vector3D{u - 0.5, v - 0.5, -1}.normalized());
    }

    Math::RGBA
    traceRay(const Ray &ray,
             const std::vector<std::unique_ptr<IShape>> &shapes) const
    {
        Math::RGBA closestColor = defaultColor;
        double minDist = std::numeric_limits<double>::infinity();

        for (const auto &shape : shapes) {
            double dist;
            Math::RGBA hitColor;
            if (shape->hits(ray, hitColor, dist) && dist < minDist) {
                minDist = dist;
                closestColor = hitColor;
            }
        }
        return closestColor;
    }

private:
    Math::RGBA defaultColor{0, 0, 0};
};

} // namespace RayTracer