/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AShape
*/

#pragma once

#include "IShape.hpp"

namespace RayTracer
{
    class AShape: public IShape {
        public:

        AShape(const Point3D &pt, const Material &material): m_point(pt), m_material(material) {}

        virtual ~AShape() = 0;

        virtual Material getMaterial() const override
        {
            return m_material;
        }

        protected:
        bool discriminant(double a, double b, double c, double &t) const;

        bool isRootValid(std::tuple<double, double> &roots) const;

        std::tuple<double, double> discriminant(double a, double b, double c)  const;

        Point3D m_point;
        Material m_material;
    };
}
