/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Glassy
*/

#pragma once

#include "Material.hpp"

namespace RayTracer {
class Glassy : public Material {
public:
    Glassy(const Math::RGBA &color)
        : Material(1.0, 5), color(color)
    {
    }
    Math::RGBA getColor(const double, const double) override { return color; }
    private:
    Math::RGBA color;
};
} // namespace RayTracer
