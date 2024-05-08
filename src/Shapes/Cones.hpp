/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cones
*/

#pragma once

#include "AShape.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Cones : public AShape {
public:
    Cones(const Point3D &center,
          const Material &material,
          double angle,
          const Vector3D &vect)
        : AShape(center, material)
        , m_vect(vect)
        , m_angle(angle)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        double dot_ray_vect = ray.m_direction.dot(m_vect);
        Vector3D ptToRay = m_point.getVectorTo(ray.m_origin);
        double cosPow = std::pow(cos(m_angle), 2);

        double a = std::pow(dot_ray_vect, 2) - cosPow;
        double b = 2 * (dot_ray_vect * (ptToRay.dot(m_vect)) -
                        (ray.m_direction.dot(ptToRay)) * cosPow);
        double c = ((ptToRay.dot(m_vect)) * (ptToRay.dot(m_vect))) -
                   ptToRay.dot(ptToRay) * cosPow;

        if (discriminant(a, b, c, t)) {
            hitColor = m_material.color;
            auto pt = ray.m_origin + ray.m_direction * t;
            if (m_angle < M_PI_2 && (pt - this->m_point).dot(this->m_vect) > 0)
                return true;
            return false;
        }
        return false;
    }

    virtual Vector3D getNormal(const Point3D &pt) const override
    {
        Vector3D axis = m_vect.normalized();
        Vector3D ptToCenter = pt - m_point;
        double height = ptToCenter.dot(axis);
        Vector3D normal = ptToCenter - axis * height;
        return normal.normalized();
    }

private:
    Vector3D m_vect;
    double m_angle;
};
} // namespace RayTracer
