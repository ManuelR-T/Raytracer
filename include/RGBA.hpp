/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RGBA
*/

#pragma once

#include <algorithm>
#include <iostream>

namespace Math {
class RGBA {
public:
    unsigned int R, G, B, A;

    RGBA(unsigned int r = 255,
         unsigned int g = 255,
         unsigned int b = 255,
         unsigned int a = 255)
        : R(r)
        , G(g)
        , B(b)
        , A(a)
    {
    }

    void clamp()
    {
        R = std::clamp<unsigned char>(R, 0, 255);
        G = std::clamp<unsigned char>(G, 0, 255);
        B = std::clamp<unsigned char>(B, 0, 255);
        A = std::clamp<unsigned char>(A, 0, 255);
    }

    void write_color(std::ostream &out) const
    {
        out << R << ' ' << G << ' ' << B << '\n';
    }
};
} // namespace Math
