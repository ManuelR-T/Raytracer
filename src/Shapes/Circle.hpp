/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Circle
*/

#pragma once

#include "AShape.hpp"
#include "Matrix/Matrix.hpp"
#include "Plane.hpp"
#include "RGBA.hpp"
#include <cmath>
#include <memory>

namespace RayTracer {
    class Circle : public AShape {
    public:
        Circle(
            const Point3D &point,
            const Vector3D &normal,
            std::unique_ptr<Material> material,
            double radius
        ):
          AShape(point, material),
          m_radius(radius)
        {
            Point3D pt = point;
            Vector3D n = normal;
            std::unique_ptr<Material> m = std::make_unique<Flat>(Math::RGBA());
            m_plan = std::make_unique<Plane>(pt, n, m);
        }

        virtual bool
        hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
        {
            if (!m_plan->hits(ray, hitColor, t))
                return false;
            Point3D pt = ray.m_origin + t * ray.m_direction;

            if (pt.getVectorTo(m_point).length() > m_radius)
                return false;
            return true;
        }

        virtual Vector3D getNormal(const Point3D &pt) const override
        {
            return m_plan->getNormal(pt);
        }

        bool isInCircle(const Point3D &pt) const
        {
            auto normal = m_plan->getNormal(pt);

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
    std::unique_ptr<RayTracer::Plane> m_plan;
    Point3D m_point;
    double m_radius;
    // height * tan(angle)
    };
} // namespace RayTracer

