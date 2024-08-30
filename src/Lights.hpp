/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Lights
*/

#pragma once

#include "RGBA.hpp"
#include "Matrix/Matrix.hpp"
#include <cmath>

namespace RayTracer {

class ILight {
public:
    virtual ~ILight() {}

    virtual Math::RGBA getIntensityAt(const Point3D& point) const = 0;
    virtual Vector3D getDirectionToPoint(const Point3D& point) const = 0;
    virtual double getLength(const Point3D& point) const = 0;
};

class DirectionalLight : public ILight {
public:
    Vector3D direction;
    Math::RGBA intensity;

    DirectionalLight(const Vector3D& dir, const Math::RGBA& intens = Math::RGBA{1, 1, 1})
        : direction(dir.normalized()), intensity(intens) {}

    virtual Math::RGBA getIntensityAt(const Point3D &) const override {
        return intensity;
    }

    virtual Vector3D getDirectionToPoint(const Point3D &) const override {
        return direction * -1;
    }

    virtual double getLength(const Point3D &) const override {
        return std::numeric_limits<double>::infinity();
    }
};

class PointLight : public ILight {
public:
    Point3D pos;
    Math::RGBA intensity;
    double attenuationFactor;

    PointLight(const Point3D& pos, const Math::RGBA& intensity = Math::RGBA{1, 1, 1}, double attenuationFactor = 1.25)
        : pos(pos), intensity(intensity), attenuationFactor(attenuationFactor) {}

    virtual Math::RGBA getIntensityAt(const Point3D& point) const override {
        double distance = pos.getVectorTo(point).length();
        double attenuation = distance / std::pow(distance, attenuationFactor);
        return intensity * attenuation;
    }

    virtual Vector3D getDirectionToPoint(const Point3D& point) const override {
        return pos.getVectorTo(point).normalized();
    }

    virtual double getLength(const Point3D& point) const override {
        return pos.getVectorTo(point).length();
    }
};

} // namespace RayTracer
