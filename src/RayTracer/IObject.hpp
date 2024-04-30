/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** IObject
*/

#pragma once

#include "Ray.hpp"
#include "Materials/Material.hpp"

namespace RayTracer {
class IObject {
public:
    virtual ~IObject()
    {
    }
    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &pt) const = 0;
};

class Sphere : public IObject {
public:
    Math::Point3D Center;
    double RadiusSq;
    RayTracer::Materials::Base mat;

    Sphere(const Math::Point3D &center,
           double radius,
           const RayTracer::Materials::Base &mat)
        : Center(center)
        , RadiusSq(radius * radius)
        , mat(mat)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &pt) const override
    {
        Math::Vector3D oc = Center.getVectorTo(ray.Origin);
        double a = ray.Direction.dot(ray.Direction);
        double b = 2.0 * oc.dot(ray.Direction);
        double c = oc.dot(oc) - RadiusSq;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            double sqrtDiscriminant = std::sqrt(discriminant);
            double t1 = (-b - sqrtDiscriminant) / (2 * a);
            double t2 = (-b + sqrtDiscriminant) / (2 * a);

            pt = t1 > 0 ? t1 : (t2 > 0 ? t2 : -1);
            if (pt < 0)
                return false;
            hitColor = mat.color;
            return true;
        }
    }
};
}