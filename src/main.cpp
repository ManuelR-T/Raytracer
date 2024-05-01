/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include <iostream>
#include "Matrix/Matrix.hpp"

int main(void)
{
    Vector3D vect1{4, 6, 42};
    Vector3D vect2{4, 4, 4};
    Math::Matrix<3, 3> rot{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << vect1 << std::endl;
    std::cout << vect1.length() << std::endl;

    std::cout << vect2.dot(vect1) << std::endl;
    std::cout << (((vect1 + vect1) * vect2) / vect2) * 2 << std::endl;
    std::cout << rot.matMul(vect1) << std::endl;

    std::cout << vect1.normalized() << std::endl;
    return 0;
}
