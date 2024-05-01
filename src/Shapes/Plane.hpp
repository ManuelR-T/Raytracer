/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Plane
*/

#pragma once

#include "../Materials/Material.hpp"
#include "IShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Plane : public IShape {
public:
    Point3D Point;
    Vector3D Normal;
    Material Jame;

    Plane(const Point3D &point,
          const Vector3D &normal,
          const Material &material)
        : Point(point)
        , Normal(normal.normalized())
        , Jame(material)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        double denominator = Normal.dot(ray.m_direction);
        if (std::abs(denominator) < 1e-6) {
            return false;
        }
        Vector3D p0_to_origin = Point.getVectorTo(ray.m_origin);
        t = p0_to_origin.dot(Normal) / denominator;
        if (t < 0) {
            return false;
        }
        hitColor = Jame.color;
        return true;
    }
};
} // namespace RayTracer
