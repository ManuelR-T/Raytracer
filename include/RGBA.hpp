/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RGBA
*/

#pragma once

#include <algorithm>
#include <iostream>

#pragma once

#include <algorithm>
#include <iostream>

namespace Math {
class RGBA {
public:
    unsigned char R, G, B, A;

    RGBA(unsigned char r = 255,
         unsigned char g = 255,
         unsigned char b = 255,
         unsigned char a = 255)
        : R(r), G(g), B(b), A(a)
    {
    }

    RGBA operator*(double scalar) const {
        return RGBA(
            static_cast<unsigned char>(std::clamp(static_cast<int>(R * scalar), 0, 255)),
            static_cast<unsigned char>(std::clamp(static_cast<int>(G * scalar), 0, 255)),
            static_cast<unsigned char>(std::clamp(static_cast<int>(B * scalar), 0, 255)),
            A  // Assuming alpha doesn't change with scalar multiplication
        );
    }

    RGBA operator*(const RGBA &other) const {
        return RGBA(
            static_cast<unsigned char>(std::min(R, other.R)),
            static_cast<unsigned char>(std::min(G, other.G)),
            static_cast<unsigned char>(std::min(B, other.B)),
            static_cast<unsigned char>(std::min(A, other.A))
        );
    }

    RGBA operator+(const RGBA &other) const {
        return RGBA(
            static_cast<unsigned char>(std::min(R + other.R, 255)),
            static_cast<unsigned char>(std::min(G + other.G, 255)),
            static_cast<unsigned char>(std::min(B + other.B, 255)),
            static_cast<unsigned char>(std::min(A + other.A, 255))
        );
    }

    RGBA &operator+=(const RGBA &other) {
        R = static_cast<unsigned char>(std::min(R + other.R, 255));
        G = static_cast<unsigned char>(std::min(G + other.G, 255));
        B = static_cast<unsigned char>(std::min(B + other.B, 255));
        A = static_cast<unsigned char>(std::min(A + other.A, 255));
        return *this;
    }

    RGBA clamp() {
        R = std::clamp(R, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
        G = std::clamp(G, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
        B = std::clamp(B, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
        A = std::clamp(A, static_cast<unsigned char>(0), static_cast<unsigned char>(255));
        return *this;
    }

    void write_color(std::ostream &out) const {
        out << static_cast<int>(R) << ' ' << static_cast<int>(G) << ' ' << static_cast<int>(B) << '\n';
    }
};
} // namespace Math

