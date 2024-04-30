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
    Vector3D vect1{4, 4, 4};
    Vector3D vect2{4, 4, 4};

    std::cout << vect1 << std::endl;
    std::cout << vect1.length() << std::endl;

    std::cout << vect2.dot(vect1) << std::endl;
    std::cout << (((vect1 + vect1) * vect2) / vect2) * 2 << std::endl;
    return 0;
}
