/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ADecoratorShape
*/

#pragma once

#include "IShape.hpp"
#include <memory>

namespace RayTracer
{
    class ADecoratorShape: public IShape {
        public:

        ADecoratorShape(std::unique_ptr<IShape> shape): wrappee(std::move(shape)) {}

        virtual ~ADecoratorShape() = default;

        virtual bool
        hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
        {
            return wrappee->hits(ray, hitColor, t);
        }

        virtual Vector3D getNormal(const Point3D &point) const override
        {
            return wrappee->getNormal(point);
        }

        std::unique_ptr<RayTracer::Material> &getMaterial() override
        {
            return wrappee->getMaterial();
        }

        protected:
        std::unique_ptr<IShape> wrappee;
    };
}
