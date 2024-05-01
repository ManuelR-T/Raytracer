/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material
*/

#pragma once

#include "RGBA.hpp"

namespace RayTracer {
class Material {
public:
    Material(const Math::RGBA &color, double refractionIndex = 1.0, double shininess = 1000.0)
        : color(color)
        , refractionIndex(refractionIndex)
        , shininess(shininess)
    {
    }

    virtual ~Material() = default;

    Math::RGBA color;
    double refractionIndex;
    double shininess;
};

} // namespace RayTracer
