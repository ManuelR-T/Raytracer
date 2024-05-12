/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

#include <algorithm>
#include <tuple>

namespace RayTracer {
bool Cylinder::hits(const Ray &ray, Math::RGBA &hitColor, double &t) const
{
    Vector3D oc = ray.m_origin - m_point;
    double a = ray.m_direction.dot(ray.m_direction) - pow(ray.m_direction.dot(m_axis), 2);
    double b = 2 * (oc).dot(ray.m_direction) - 2 * (oc).dot(m_axis) * ray.m_direction.dot(m_axis);
    double c = (oc).dot(oc) - pow((oc).dot(m_axis), 2) - m_radius * m_radius;

    if (!discriminant(a,b,c,t))
        return false;

    Point3D hitPoint = ray.m_origin + ray.m_direction * t;

    std::tuple<double, double> uv = getUV(hitPoint, getNormal(hitPoint));

    hitColor = m_material->getColor(std::get<0>(uv), std::get<1>(uv));
    return true;
}

Vector3D Cylinder::getNormal(const Point3D &hitPoint) const
{
    Point3D projection = m_point + m_axis * ((hitPoint - m_point).dot(m_axis));
    Vector3D normal = (hitPoint - projection).normalized();
    return normal;
}
} // namespace RayTracer
