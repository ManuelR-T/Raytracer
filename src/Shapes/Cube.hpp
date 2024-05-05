/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#pragma once

#include "../Materials/Material.hpp"
#include "AShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Cube : public AShape {
public:
    Cube(const Point3D &center, double size, const Material &material)
        : AShape(center, material), m_size(size) {}

    virtual bool hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;
    virtual Vector3D getNormal(const Point3D &hitPoint) const override;

private:
    double m_size;
};
} // namespace RayTracer
