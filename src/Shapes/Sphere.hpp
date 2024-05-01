/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Sphere
*/

#pragma once

#include "../Materials/Material.hpp"
#include "IShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Sphere : public IShape {
public:
    Point3D Center;
    double Radius;
    Material jame;

    Sphere(const Point3D &center, double radius, const Material &color)
        : Center(center)
        , Radius(radius)
        , jame(color)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        Vector3D oc = Center.getVectorTo(ray.m_origin);
        double a = ray.m_direction.dot(ray.m_direction);
        double b = 2.0 * oc.dot(ray.m_direction);
        double c = oc.dot(oc) - Radius * Radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            double sqrtDiscriminant = std::sqrt(discriminant);
            double t1 = (-b - sqrtDiscriminant) / (2 * a);
            double t2 = (-b + sqrtDiscriminant) / (2 * a);

            t = t1 > 0 ? t1 : (t2 > 0 ? t2 : -1);
            if (t < 0)
                return false;

            hitColor = jame.color;
            return true;
        }
    }

    virtual Vector3D getNormal(const Point3D &point) const override
    {
        return point.getVectorTo(Center).normalized();
    }
};
} // namespace RayTracer
