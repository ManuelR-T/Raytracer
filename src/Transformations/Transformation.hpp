/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Transformation
*/

#pragma once

#include "Matrix/Matrix.hpp"

namespace Math {

class Transformation3D {
public:
    static void rotateX(Vector3D &vect, double angle);
    static void rotateY(Vector3D &vect, double angle);
    static void rotateZ(Vector3D &vect, double angle);

    static void translate(Vector3D &vect, const Vector3D &factor);

    static void scale(Vector3D &vect, const Vector3D &factor);
    static void shear(Vector3D &vect, const std::array<double, 6> &fact);

private:
    static void transform(Matrix<4, 4> &mat, Vector4D &dVect, Vector3D &vect);
};

} // namespace Math
