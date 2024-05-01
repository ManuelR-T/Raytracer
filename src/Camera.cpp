/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera
*/

#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include "Raytracer.hpp"
#include "Scene.hpp"
#include "Shapes/IShape.hpp"

#include <memory>

namespace RayTracer {
Camera::Camera(const Point3D &origin) : origin(origin)
{
}

Ray Camera::ray(double u, double v) const
{
    return Ray(origin, Vector3D{u - 0.5, v - 0.5, -1}.normalized());
}

Math::RGBA Camera::traceRay(const Ray &ray, const Scene &scene) const
{
    double minDist = std::numeric_limits<double>::infinity();
    Math::RGBA closestColor = Math::RGBA{0, 0, 0, 0};
    Point3D hitPoint;
    IShape *closestShape = nullptr;

    for (const auto &shape : scene.shapes) {
        double dist;
        Math::RGBA hitColor;
        if (shape->hits(ray, hitColor, dist) && dist < minDist && dist > 0) {
            minDist = dist;
            closestColor = hitColor;
            closestShape = shape.get();
            hitPoint = ray.m_origin + ray.m_direction * dist;
        }
    }

    if (closestShape) {
        Math::RGBA finalColor = Math::RGBA{0, 0, 0, 0};
        for (const auto &light : scene.lights) {
            Vector3D lightDir =
                light->getDirectionFromLightToPoint(hitPoint).normalized();
            Math::RGBA lightIntensity = light->getIntensityAt(hitPoint);
            Vector3D normal = closestShape->getNormal(hitPoint);
            double dot = lightDir.dot(normal);

            if (dot > 0) {
                finalColor += closestColor * (lightIntensity * dot);
            }
        }
        return finalColor;
    }
    return closestColor;
}
} // namespace RayTracer