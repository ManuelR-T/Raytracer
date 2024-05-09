/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cones
*/

#pragma once

#include "ADecoratorShape.hpp"
#include "AShape.hpp"
#include "Circle.hpp"

#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include <memory>

namespace RayTracer {
    class Cones : public AShape {
    public:
        Cones(const Point3D &center,
              const Material &material,
              double angle,
              const Vector3D &vect,
              double height)
            : AShape(center, material)
            , m_vect(vect)
            , m_angle(angle)
            , m_height(height)
        {
        }

        virtual bool
        hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;

        virtual Vector3D getNormal(const Point3D &pt) const override;

    private:
        bool pointInConeValid(const Point3D &pt) const;

        Vector3D m_vect;
        double m_angle;
        double m_height;
    };

    class LimitedCones : public ADecoratorShape {
    public:
        LimitedCones(const Point3D &center,
              const Material &material,
              double angle,
              const Vector3D &vect,
              double height)
            :
              ADecoratorShape(std::make_unique<Cones>(
                Cones(center, material, angle, vect, height)))
            , m_circle(center + vect, vect, Material(Math::RGBA{255, 255, 255}), height * tan(angle))
        {
        }

        virtual bool
        hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;

        virtual Vector3D getNormal(const Point3D &point) const override;

        virtual Material getMaterial() const override;

        private:
        Circle m_circle;
    };

} // namespace RayTracer
