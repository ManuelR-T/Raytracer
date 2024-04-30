/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Vector3D
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

namespace Math {

class Vector3D {
public:
    double X = 0, Y = 0, Z = 0;

    Vector3D() = default;

    Vector3D(double x, double y, double z) : X(x), Y(y), Z(z)
    {
    }

    double length() const
    {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    void normalize()
    {
        double len = length();
        if (len != 0) {
            X /= len;
            Y /= len;
            Z /= len;
        }
    }

    Vector3D normalized() const
    {
        double len = length();
        if (len == 0) {
            return *this;
        }
        return {X / len, Y / len, Z / len};
    }

    Vector3D operator+(const Vector3D &other) const
    {
        return {X + other.X, Y + other.Y, Z + other.Z};
    }

    Vector3D &operator+=(const Vector3D &other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D operator-(const Vector3D &other) const
    {
        return {X - other.X, Y - other.Y, Z - other.Z};
    }

    Vector3D &operator-=(const Vector3D &other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D operator*(double scalar) const
    {
        return {X * scalar, Y * scalar, Z * scalar};
    }

    Vector3D &operator*=(double scalar)
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    Vector3D operator/(double scalar) const
    {
        return {X / scalar, Y / scalar, Z / scalar};
    }

    Vector3D &operator/=(double scalar)
    {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    double dot(const Vector3D &other) const
    {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    Vector3D cross(const Vector3D &other) const
    {
        return {Y * other.Z - Z * other.Y,
                Z * other.X - X * other.Z,
                X * other.Y - Y * other.X};
    }
};

class Point3D {
public:
    double X = 0, Y = 0, Z = 0;

    Point3D() = default;

    Point3D(double x, double y, double z) : X(x), Y(y), Z(z)
    {
    }

    Vector3D getVectorTo(const Point3D &other) const
    {
        return {other.X - X, other.Y - Y, other.Z - Z};
    }

    Vector3D getVectorFrom(const Point3D &other) const
    {
        return {X - other.X, Y - other.Y, Z - other.Z};
    }

    Point3D operator+(const Vector3D &vec) const
    {
        return {X + vec.X, Y + vec.Y, Z + vec.Z};
    }
};

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
