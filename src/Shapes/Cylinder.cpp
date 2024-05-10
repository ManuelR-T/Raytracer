/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"
#include "Matrix/Matrix.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>

bool RayTracer::Cylinder::hits(const Ray &ray, Math::RGBA &hitColor, double &t) const
{
    double a = (std::pow(ray.m_direction[0],2) + std::pow(ray.m_direction[2], 2));
    double b = 2.0 * ((ray.m_direction[0] * -m_point[0]) + (ray.m_direction[2] * -m_point[2]));
    double c = std::pow(m_point[0], 2) + std::pow(m_point[2], 2) - m_size * m_size;

    if (discriminant(a, b, c, t)) {
        hitColor = m_material.color;

        // double d = (-m_point.y()) / ray.m_direction.y();
        // double e = (m_height - m_point.y()) / ray.m_direction.y();
        // double t3 = std::min(d, e);
        // double t4 = std::max(d, e);
        // t = (t3 < t4) ? t3 : t4;
        return true;
    }
    return false;
}

Vector3D RayTracer::Cylinder::getNormal(const Point3D &hitPoint) const
{
    return (Vector3D{hitPoint[0] - m_point[0], 0, hitPoint[2] - m_point[2]}).normalized();
}