/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AShape
*/

#include "AShape.hpp"

// To make AShape Abstract class
RayTracer::AShape::~AShape()
{
}

bool RayTracer::AShape::discriminant(double a,
                                     double b,
                                     double c,
                                     double &t) const
{
    double delta = b * b - 4 * a * c;
    if (delta < 0) {
        return false;
    } else {
        double sqrtDiscriminant = std::sqrt(delta);
        double t1 = (-b - sqrtDiscriminant) / (2 * a);
        double t2 = (-b + sqrtDiscriminant) / (2 * a);

        t = (t1 < t2) ? t1 : t2;
        if (t < 0)
            return false;
        return true;
    }
}
