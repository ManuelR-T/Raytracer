/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Ray
*/

#pragma once

#include "Vector3D.hpp"

namespace RayTracer {
class Ray {
public:
    Math::Point3D Origin;
    Math::Vector3D Direction;

    Ray() = default;
    Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
        : Origin(origin)
        , Direction(direction)
    {
    }
};
} // namespace RayTracer
