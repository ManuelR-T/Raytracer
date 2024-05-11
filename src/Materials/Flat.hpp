/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Flat
*/

#pragma once

#include "Material.hpp"

namespace RayTracer {
class Flat : public Material {
public:
    Flat(const Math::RGBA &color)
        : Material(1.0, 0), color(color)
    {
    }
    Math::RGBA getColor(const double, const double) override { return color; }
    private:
    Math::RGBA color;
};
} // namespace RayTracer