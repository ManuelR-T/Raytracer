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
        : Material(color, 1.0, 100000)
    {
    }
};
} // namespace RayTracer