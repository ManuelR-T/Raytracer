/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IShape
*/

#pragma once

#include "../Materials/Materials.hpp"
#include "../Raytracer.hpp"
#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"

namespace RayTracer {

class IShape {
public:
    virtual ~IShape() = default;

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const = 0;

    virtual Vector3D getNormal(const Point3D &point) const = 0;
    virtual Material getMaterial() const = 0;
};

} // namespace RayTracer
