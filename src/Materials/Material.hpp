/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material
*/

#pragma once

#include "RGBA.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {
class Material {
public:
    Material(double refractionIndex = 1.0, double shininess = 1000.0)
        : refractionIndex(refractionIndex)
        , shininess(shininess)
    {
    }
    Material(const Material &other) = default;

    virtual ~Material() = default;
    virtual Math::RGBA getColor(const double u, const double v) = 0;

    double refractionIndex;
    double shininess;
};

} // namespace RayTracer
