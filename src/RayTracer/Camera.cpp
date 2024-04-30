/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Camera
*/

#include "Camera.hpp"

namespace RayTracer {
Camera::Camera(const Math::Point3D &origin) : origin(origin)
{
}

Ray Camera::ray(double u, double v) const
{
    return Ray(origin, Math::Vector3D(u - 0.5, v - 0.5, -1).normalized());
}

Math::RGBA
Camera::traceRay(const Ray &ray,
                 const std::vector<std::unique_ptr<IObject>> &shapes) const
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
} // namespace RayTracer