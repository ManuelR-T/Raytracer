/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Transformation
*/

#include "Transformation.hpp"

#include <cmath>
#include <iostream>

void Math::Transformation3D::rotateX(Vector3D &vect, double angle)
{
    Matrix<4, 4> rotX{
        1,  0,           0,            0,
        0,  cos(angle),  -sin(angle),  0,
        0,  sin(angle),  cos(angle),   0,
        0,  0,           0,            1
    };
    Vector4D dVect = vect.addRow();
    transform(rotX, dVect, vect);
    vect.normalize();
}

void Math::Transformation3D::rotateY(Vector3D &vect, double angle)
{
    Matrix<4, 4> rotY{
        cos(angle),   0,  sin(angle),  0,
        0,            1,  0,           0,
        -sin(angle),  0,  cos(angle),  0,
        0,            0,  0,           1
    };
    Vector4D dVect = vect.addRow();
    transform(rotY, dVect, vect);
    vect.normalize();
}

void Math::Transformation3D::rotateZ(Vector3D &vect, double angle)
{
    Matrix<4, 4> rotZ{
        cos(angle),  -sin(angle), 0,  0,
        sin(angle),  cos(angle),  0,  0,
        0,           0,           1,  0,
        0,           0,           0,  1
    };
    Vector4D dVect = vect.addRow();
    transform(rotZ, dVect, vect);
    vect.normalize();
}

void Math::Transformation3D::translate(Vector3D &vect, const Vector3D &factor)
{
    double tX = factor(0, 0);
    double tY = factor(1, 0);
    double tZ = factor(1, 0);

    Matrix<4, 4> translate{
        1,  0,  0,  tX,
        0,  1,  0,  tY,
        0,  0,  1,  tZ,
        0,  0,  0,  1
    };
    Vector4D dVect = vect.addRow();
    transform(translate, dVect, vect);
}

void Math::Transformation3D::scale(Vector3D &vect, const Vector3D &factor)
{
    double sX = factor(0, 0);
    double sY = factor(1, 0);
    double sZ = factor(1, 0);


    Matrix<4, 4> scaling{
        sX,  0,   0,   0,
        0,   sY,  0,   0,
        0,   0,   sZ,  0,
        0,   0,   0,   1
    };
    Vector4D dVect = vect.addRow();
    transform(scaling, dVect, vect);
}

void Math::Transformation3D::shear(Vector3D &vect, const std::array<double, 6> &fact)
{
    Matrix<4, 4> shearing{
        1,       fact[0], fact[1], 0,
        fact[2], 1,       fact[3], 0,
        fact[4], fact[5], 1,       0,
        0,       0,       0,       1
    };
    Vector4D dVect = vect.addRow();
    transform(shearing, dVect, vect);
}

void Math::Transformation3D::transform(Matrix<4, 4> &mat, Vector4D &dVect, Vector3D &vect)
{
    Vector4D newVect = mat.matMul(dVect);

    vect(0, 0) = newVect(0, 0);
    vect(1, 0) = newVect(1, 0);
    vect(2, 0) = newVect(2, 0);
}
