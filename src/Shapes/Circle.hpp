/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Circle
*/

#pragma once

#include "AShape.hpp"
#include "Plane.hpp"

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
            auto vect = m_point.getVectorTo(pt);

            if (vect.dot(m_plan.getNormal(pt)) == 0)
                return true;
            return true;
        }

    private:
    RayTracer::Plane m_plan;
    Point3D m_point;
    double m_radius;
    // height * tan(angle)
    };
} // namespace RayTracer

