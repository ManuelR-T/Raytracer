/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Material
*/

#pragma once

#include "Vector3D.hpp"

namespace RayTracer {
namespace Materials {
class Base {
public:
    Math::RGBA color;
    double refractionIndex;

    Base(const Math::RGBA &color, double refractionIndex = 1.0)
        : color(color)
        , refractionIndex(refractionIndex)
    {
    }

    virtual ~Base() = default;
};

class Flat : public Base {
public:
    Flat(const Math::RGBA &color) : Base(color, 1.0)
    {
    }
};

} // namespace Materials
} // namespace Raytracer