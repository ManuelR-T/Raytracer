/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cones
*/

#include "Cones.hpp"
#include "Matrix/Matrix.hpp"
#include <cmath>
#include <limits>
#include <memory>

bool RayTracer::Cones::hits(const Ray &ray,
                            Math::RGBA &hitColor,
                            double &t) const
{
    double dot_ray_vect = ray.m_direction.dot(m_vect);
    Vector3D ptToRay = m_point.getVectorTo(ray.m_origin);
    double cosPow = std::pow(cos(m_angle), 2);

    double a = std::pow(dot_ray_vect, 2) - cosPow;
    double b = 2 * (dot_ray_vect * (ptToRay.dot(m_vect)) -
                    (ray.m_direction.dot(ptToRay)) * cosPow);
    double c = ((ptToRay.dot(m_vect)) * (ptToRay.dot(m_vect))) -
               ptToRay.dot(ptToRay) * cosPow;

    std::tuple<double, double> roots = discriminant(a, b, c);
        if (isRootValid(roots)) {

        Point3D hitPoint = ray.m_origin + ray.m_direction * std::get<0>(roots);
        Vector3D normal = getNormal(hitPoint);
        Vector3D tangentU = normal.cross(Vector3D({1, 0, 0})).normalized();
        if (tangentU.length() < 1e-6) {
            tangentU = normal.cross(Vector3D({0, 1, 0})).normalized();
        }
        Vector3D tangentV = normal.cross(tangentU).normalized();

        double u = hitPoint.dot(tangentU);
        double v = hitPoint.dot(tangentV);

        hitColor = m_material->getColor(u,v);
        double t1, t2;

        std::tie(t1, t2) = roots;

        if (t1 != std::numeric_limits<double>::infinity()
            && pointInConeValid(ray.m_origin + ray.m_direction * t1)) {
            t = t1;
            return true;
        }

        if (t2 != std::numeric_limits<double>::infinity()
            && pointInConeValid(ray.m_origin + ray.m_direction * t2)) {
            t = t2;
            return true;
        }

        return false;
    }
    return false;
}

Vector3D RayTracer::Cones::getNormal(const Point3D &pt) const
{
    Vector3D axis = m_vect.normalized();
    Vector3D ptToCenter = pt - m_point;
    double height = ptToCenter.dot(axis);
    Vector3D normal = ptToCenter - axis * height;
    return normal.normalized();
}

bool RayTracer::Cones::pointInConeValid(const Point3D &pt) const
{
    Vector3D ptToCenter = pt - m_point;
    double dist = ptToCenter.length() * cos(m_angle);

    if (dist < 0 || dist > m_height)
        return false;
    if (m_angle < M_PI_2 && (pt - this->m_point).dot(this->m_vect) > 0)
        return true;
    return false;
}

bool RayTracer::LimitedCones::hits(const Ray &ray, Math::RGBA &hitColor, double &t) const
{
    Math::RGBA coneColor;
    double tCone;

    if (!this->wrappee->hits(ray, coneColor, tCone))
        return false;

    Math::RGBA circleColor;
    double tCircle;

    bool isCircle = m_circle.hits(ray, circleColor, tCircle);

    Point3D ptToCone = ray.m_origin + tCone * ray.m_direction;
    Point3D ptToCircle = ray.m_origin + tCircle * ray.m_direction;

    if (isCircle && ptToCircle.length() < ptToCone.length()) {
        t = tCircle;
        hitColor = circleColor;
        return true;
    }
    t = tCone;
    hitColor = coneColor;
    return true;
}

Vector3D RayTracer::LimitedCones::getNormal(const Point3D &point) const
{
    if (m_circle.isInCircle(point)) {
        return m_circle.getNormal(point);
    }
    return wrappee->getNormal(point);
}


