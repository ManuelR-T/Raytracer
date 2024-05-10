/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#pragma once
#include "../Materials/Material.hpp"
#include "AShape.hpp"
#include "Matrix/Matrix.hpp"
#include <cstddef>

namespace RayTracer {

    class Cylinder : public AShape {
        public:
            Cylinder(const Point3D &center, double radius, const Vector3D &axis, const Material &mat) : AShape(center, mat), m_size(radius), m_height(axis.length()), m_vec(axis) {}

        virtual bool hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override;
        virtual Vector3D getNormal(const Point3D &hitPoint) const override;

        private:
            double m_size;
            std::size_t m_height;
            Vector3D m_vec;
    };
}