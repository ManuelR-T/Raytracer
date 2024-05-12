/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#pragma once

#include "../Materials/Material.hpp"
#include "AShape.hpp"
#include "Matrix/Matrix.hpp"
#include <memory>

namespace RayTracer {
class Cylinder : public AShape {
public:
    Cylinder(const Point3D &center,
             double radius,
             const Vector3D &axis,
             const double height,
             std::unique_ptr<Material> material)
        : AShape(center, material)
        , m_radius(radius)
        , m_height(height)
        , m_axis(axis)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;
    virtual Vector3D getNormal(const Point3D &hitPoint) const override;

private:
    double m_radius;
    double m_height;
    Vector3D m_axis;
};
} // namespace RayTracer
