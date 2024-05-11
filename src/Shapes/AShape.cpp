/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AShape
*/

#include "AShape.hpp"
#include <limits>
#include <tuple>

// To make AShape Abstract class
RayTracer::AShape::~AShape()
{
}

std::tuple<double, double> RayTracer::AShape::getUV(const Point3D &hitPoint, const Vector3D &normal) const
{
    Vector3D tangentU = normal.cross(Vector3D({1, 0, 0})).normalized();
    if (tangentU.length() < 1e-6) {
        tangentU = normal.cross(Vector3D({0, 1, 0})).normalized();
    }
    Vector3D tangentV = normal.cross(tangentU).normalized();

    double u = hitPoint.dot(tangentU);
    double v = hitPoint.dot(tangentV);

    return std::make_tuple(u, v);
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

std::tuple<double, double> RayTracer::AShape::discriminant(double a, double b, double c) const
{
    double delta = b * b - 4 * a * c;
    auto inf = std::numeric_limits<double>::infinity();

    if (delta < 0)
        return std::make_tuple(inf, inf);
    double sqrtDiscriminant = std::sqrt(delta);
    double t1 = (-b - sqrtDiscriminant) / (2 * a);
    double t2 = (-b + sqrtDiscriminant) / (2 * a);

    if (delta == 0)
        return std::make_tuple((t1 < t2) ? t1 : t2, inf);
    return std::make_tuple((t1 < t2) ? t1 : t2, (t1 < t2) ? t2 : t1);
}

bool RayTracer::AShape::isRootValid(std::tuple<double, double> &roots) const
{
    double t1, t2;
    auto inf = std::numeric_limits<double>::infinity();

    std::tie(t1, t2) = roots;
    if (t1 == inf && t2 == inf)
        return false;
    return true;
}
