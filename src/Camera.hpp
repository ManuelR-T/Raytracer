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
#include <memory>
#include "Shapes/IShape.hpp"

namespace RayTracer {

class Scene;
class Camera {
public:
    Point3D origin;
    Vector3D direction; // Orientation of the camera
    Vector3D up;        // Up direction for the camera

    Camera(const Point3D &origin = Point3D{0, 0, 0},
           const Vector3D &direction = Vector3D{0, 0, -1},
           const Vector3D &up = Vector3D{0, 1, 0});

    Ray ray(double u, double v, double fov = 90.0, double aspectRatio = 8.0/6) const;
    Math::RGBA traceRay(const Ray &ray, const Scene &scene, bool isLight) const;

private:

    static void applyLight(
        const Scene &scene,
        const std::vector<std::unique_ptr<IShape>>::const_iterator &closestShapeIt,
        const Math::RGBA &closestColor,
        const Point3D &hitPoint,
        Math::RGBA &finalColor,
        const Vector3D &viewDir
    );

    static std::tuple<double, Math::RGBA, Point3D, std::vector<std::unique_ptr<IShape>>::const_iterator>
    getClosestShapeInfo(const Ray &ray, const Scene &scene);

    static void applyDiffuseLight(
        Math::RGBA &loopColor,
        const Math::RGBA &closestColor,
        const Math::RGBA &lightColor,
        double dot
    );

    static void applySpecularLight(
        Math::RGBA &loopColor,
        const Math::RGBA &lightColor,
        double dot,
        const Vector3D &viewDir,
        const Vector3D &lightDir,
        const Vector3D &normal,
        const std::vector<std::unique_ptr<IShape>>::const_iterator &closestShapeIt
    );

    Math::RGBA defaultColor{0, 0, 0};
};
} // namespace RayTracer
