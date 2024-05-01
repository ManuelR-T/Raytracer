/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material
*/

#pragma once

#include "RGBA.hpp"

namespace RayTracer
{
    class Material {
    public:

        Material(const Math::RGBA &color, double refractionIndex = 1.0)
            : color(color)
            , refractionIndex(refractionIndex)
        {
        }

        virtual ~Material() = default;

        Math::RGBA color;
        double refractionIndex;
    };

    class Flat : public Material {
    public:
        Flat(const Math::RGBA &color, double refractionIndex = 1.0)
            : Material(color, refractionIndex)
        {
        }
    };

}

