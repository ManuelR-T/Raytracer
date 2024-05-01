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
    Flat(const Math::RGBA &color, double refractionIndex = 1.0, double shininess = 10)
        : Material(color, refractionIndex, shininess)
    {
    }
};
} // namespace RayTracer