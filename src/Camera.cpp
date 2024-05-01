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
    auto closestShapeIt = scene.shapes.end();

    for (auto it = scene.shapes.begin(); it != scene.shapes.end(); ++it) {
        double dist;
        Math::RGBA hitColor;
        if ((*it)->hits(ray, hitColor, dist) && dist < minDist && dist > 0) {
            minDist = dist;
            closestColor = hitColor;
            closestShapeIt = it;
            hitPoint = ray.m_origin + ray.m_direction * dist;
        }
    }

    if (closestShapeIt != scene.shapes.end()) {

        Math::RGBA finalColor = scene.ambientLight * closestColor;
        Vector3D viewDir = (ray.m_direction * -1).normalized();
        for (const auto &light : scene.lights) {
            Math::RGBA loopColor = Math::RGBA{0, 0, 0, 1};
            Vector3D lightDir = light->getDirectionToPoint(hitPoint).normalized();
            Math::RGBA lightColor = light->getIntensityAt(hitPoint);
            Vector3D normal = (*closestShapeIt)->getNormal(hitPoint);
            double dot = std::max(lightDir.dot(normal), 0.0);

            // Diffuse light
            if (dot > 0) {
                loopColor.R = closestColor.R * lightColor.R * dot / 255.0;
                loopColor.G = closestColor.G * lightColor.G * dot / 255.0;
                loopColor.B = closestColor.B * lightColor.B * dot / 255.0;
            }

            // Specular light
            Vector3D reflectDir = (2 * dot * normal - lightDir).normalized();
            double spec = std::pow(std::max(viewDir.dot(reflectDir), .0), (*closestShapeIt)->getMaterial().shininess);
            loopColor += lightColor * spec;


            finalColor += loopColor;

        }
        return finalColor.clamp();
    }
    return closestColor;
}
} // namespace RayTracer
