/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** IShape
*/

#pragma once

#include "../Raytracer.hpp"
#include "RGBA.hpp"

namespace RayTracer {

class IShape {
public:
    virtual ~IShape()
    {
    }
    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const = 0;
};
} // namespace RayTracer