/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Raytracer
*/

#pragma once

#include "RGBA.hpp"
#include "Material.hpp"
#include "Matrix/Matrix.hpp"

#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

namespace RayTracer {
    class Ray {
    public:

        Ray() = default;
        Ray(const Point3D &origin, const Vector3D &direction)
            : m_origin(origin)
            , m_direction(direction)
        {
        }
        Point3D m_origin;
        Vector3D m_direction;
    };
}
