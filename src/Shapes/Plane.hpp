/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#pragma once

#include "../Materials/Material.hpp"
#include "AShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Plane : public AShape {
public:

    Plane(const Point3D &point,
          const Vector3D &normal,
          const Material &material)
        :
          AShape(point, material)
        , m_normal(normal.normalized())
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        double denominator = m_normal.dot(ray.m_direction);
        if (std::abs(denominator) < 1e-6) {
            return false;
        }
        Vector3D p0_to_origin = m_point.getVectorTo(ray.m_origin);
        t = p0_to_origin.dot(m_normal) / denominator;
        if (t < 0) {
            return false;
        }
        hitColor = m_material.color;
        return true;
    }

    virtual Vector3D getNormal(const Point3D &) const override
    {
        return m_normal;
    }

    private:
    Vector3D m_normal;
};
} // namespace RayTracer
