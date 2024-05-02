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
        : Material(color, 1.0, 10)
    {
    }
};
} // namespace RayTracer
