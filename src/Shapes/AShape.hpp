/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AShape
*/

#pragma once

#include "IShape.hpp"
#include <memory>
#include <utility>

namespace RayTracer
{
    class AShape: public IShape {
        public:

        AShape(const Point3D &pt, std::unique_ptr<Material> &material)
    : m_point(pt), m_material(std::move(material)) {}


        virtual ~AShape();

        virtual std::unique_ptr<Material> &getMaterial() override
        {
            return m_material;
        }

        protected:
        bool discriminant(double a, double b, double c, double &t) const;
        std::tuple<double, double> getUV(const Point3D &hitPoint, const Vector3D &normal) const;

        bool isRootValid(std::tuple<double, double> &roots) const;

        std::tuple<double, double> discriminant(double a, double b, double c)  const;

        Point3D m_point;
        std::unique_ptr<Material> m_material;
    };
}
