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
#include "../Materials/Materials.hpp"

#include "Matrix/Matrix.hpp"
#include "RGBA.hpp"
#include <memory>

namespace RayTracer {
class Cones : public AShape {
public:
    Cones(const Point3D &center,
          std::unique_ptr<RayTracer::Material> material,
          double angle,
          const Vector3D &vect)
        : AShape(center, material)
        , m_vect(vect)
        , m_angle(angle)
        , m_height(vect.length())
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
                 std::unique_ptr<Material> material,
                 double angle,
                 const Vector3D &vect)
        : ADecoratorShape(
              std::make_unique<Cones>(center, std::move(material), angle, vect)),
          m_circle(center + vect, vect, std::make_unique<Flat>(Math::RGBA()) , vect.length() * tan(angle))
    {
    }


    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;

    virtual Vector3D getNormal(const Point3D &point) const override;

private:
    Circle m_circle;
};

} // namespace RayTracer
