/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lights
*/

#pragma once

#include "RGBA.hpp"
#include "Matrix/Matrix.hpp"

namespace RayTracer {

class ILight {
public:
    virtual ~ILight() {}

    virtual Math::RGBA getIntensityAt(const Point3D& point) const = 0;
    virtual Vector3D getDirectionFromLightToPoint(const Point3D& point) const = 0;
};

class DirectionalLight : public ILight {
public:
    Vector3D direction;
    Math::RGBA intensity;

    DirectionalLight(const Vector3D& dir, const Math::RGBA& intens = Math::RGBA{1, 1, 1})
        : direction(dir.normalized()), intensity(intens) {}

    virtual Math::RGBA getIntensityAt(const Point3D& point) const override {
        return intensity;
    }

    virtual Vector3D getDirectionFromLightToPoint(const Point3D& point) const override {
        return direction * -1;
    }
};

class PointLight : public ILight {
public:
    Point3D position;
    Math::RGBA intensity;

    PointLight(const Point3D& pos, const Math::RGBA& intens = Math::RGBA{1, 1, 1})
        : position(pos), intensity(intens) {}

    virtual Math::RGBA getIntensityAt(const Point3D& point) const override {
        return intensity;
    }

    virtual Vector3D getDirectionFromLightToPoint(const Point3D& point) const override {
        return position.getVectorTo(point).normalized();
    }
};

} // namespace RayTracer

