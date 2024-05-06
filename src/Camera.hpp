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
    Vector3D direction; // Orientation of the camera
    Vector3D up;        // Up direction for the camera

    Camera(const Point3D &origin = Point3D{0, 0, 0},
           const Vector3D &direction = Vector3D{0, 0, -1},
           const Vector3D &up = Vector3D{0, 1, 0});

    Ray ray(double u, double v, double fov = 90.0, double aspectRatio = 8.0/6) const;
    Math::RGBA traceRay(const Ray &ray, const Scene &scene) const;

private:
    Math::RGBA defaultColor{0, 0, 0};
};
} // namespace RayTracer
