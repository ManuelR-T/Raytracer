/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cube
*/

#include "Cube.hpp"

#include "Cube.hpp"
#include "Matrix/Matrix.hpp"
#include <algorithm>

namespace RayTracer {
bool Cube::hits(const Ray &ray, Math::RGBA &hitColor, double &t) const
{
    double tMin = 0;
    double tMax = std::numeric_limits<double>::infinity();
    Point3D bounds[2] = {
        m_point - Point3D({m_size / 2, m_size / 2, m_size / 2}),
        m_point + Point3D({m_size / 2, m_size / 2, m_size / 2})};

    for (int i = 0; i < 3; ++i) { // Check for x, y, z axes
        double invD = 1.0 / ray.m_direction[i];
        double t0 = (bounds[0][i] - ray.m_origin[i]) * invD;
        double t1 = (bounds[1][i] - ray.m_origin[i]) * invD;
        if (invD < 0.0)
            std::swap(t0, t1);
        tMin = t0 > tMin ? t0 : tMin;
        tMax = t1 < tMax ? t1 : tMax;
        if (tMax <= tMin)
            return false;
    }

    t = tMin;
    hitColor = m_material.color;
    return true;
}

Vector3D Cube::getNormal(const Point3D &hitPoint) const
{
    Vector3D hitVec = hitPoint - m_point;
    hitVec = hitVec / (m_size / 2);
    Vector3D normal;
    if (std::abs(hitVec.x()) > std::abs(hitVec.y()) &&
        std::abs(hitVec.x()) > std::abs(hitVec.z())) {
        normal = Vector3D({(hitVec.x() > 0) ? 1.0 : -1.0, 0, 0});
    } else if (std::abs(hitVec.y()) > std::abs(hitVec.x()) &&
               std::abs(hitVec.y()) > std::abs(hitVec.z())) {
        normal = Vector3D({0, ((hitVec.y() > 0) ? 1.0 : -1.0), 0});
    } else {
        normal = Vector3D({0, 0, ((hitVec.z() > 0) ? 1.0 : -1.0)});
    }
    return normal;
}
} // namespace RayTracer
