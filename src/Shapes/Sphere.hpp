/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#pragma once

#include "../Materials/Material.hpp"
#include "AShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Sphere : public AShape {
public:

    Sphere(const Point3D &center, double radius, const Material &material):
          AShape(center, material)
        , m_radius(radius)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        Vector3D oc = m_point.getVectorTo(ray.m_origin);
        double a = ray.m_direction.dot(ray.m_direction);
        double b = 2.0 * oc.dot(ray.m_direction);
        double c = oc.dot(oc) - m_radius * m_radius;

        if (discriminant(a, b, c, t)) {
            hitColor = m_material.color;
            return true;
        }
        return false;
    }

    virtual Vector3D getNormal(const Point3D &othPoint) const override
    {
        return m_point.getVectorTo(othPoint).normalized();
    }

private:
    double m_radius;
};
} // namespace RayTracer
