/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ChessBoard
*/

#pragma once

#include "Material.hpp"

namespace RayTracer {
class ChessBoard : public Material {
public:
    ChessBoard(const Math::RGBA &color,
               const Math::RGBA &color2,
               double scale = 1.0)
        : Material(1.0, 5)
        , color1(color)
        , color2(color2)
        , scale(scale)
    {
    }
    Math::RGBA getColor(const double u, const double v) override {
        double val = std::sin(u / scale) * std::sin(v / scale);
        if (val < 0) {
            return color1;
        }
        return color2;
}


private:
    Math::RGBA color1;
    Math::RGBA color2;
    double scale;
};
} // namespace RayTracer
