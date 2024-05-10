/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Circle
*/

#pragma once

#include "AShape.hpp"
#include "Plane.hpp"
#include <cmath>

namespace RayTracer {
    class Circle : public AShape {
    public:

        Circle(
            const Point3D &point,
            const Vector3D &normal,
            const Material &material,
            double radius
        ):
          AShape(point, material)
        , m_plan(point, normal, material)
        , m_point(point)
        , m_radius(radius)
        {
        }

        virtual bool
        hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
        {
            if (!m_plan.hits(ray, hitColor, t))
                return false;
            Point3D pt = ray.m_origin + t * ray.m_direction;

            if (pt.getVectorTo(m_point).length() > m_radius)
                return false;
            return true;
        }

        virtual Vector3D getNormal(const Point3D &pt) const override
        {
            return m_plan.getNormal(pt);
        }

        bool isInCircle(const Point3D &pt) const
        {
            auto normal = m_plan.getNormal(pt);

            double isPoint =
                std::pow(pt.x() - m_point.x(), 2) +
                std::pow(pt.y() - m_point.y(), 2) +
                std::pow(pt.z() - m_point.z(), 2);

            auto vect = m_point.getVectorTo(pt);

            if (isPoint <= m_radius && vect.dot(normal) == 0)
                return true;
            return false;
        }

    private:
    RayTracer::Plane m_plan;
    Point3D m_point;
    double m_radius;
    // height * tan(angle)
    };
} // namespace RayTracer

