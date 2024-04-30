/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Raytracer
*/

#pragma once

#include "Vector3D.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

namespace RayTracer {

class Ray {
public:
    Math::Point3D Origin;
    Math::Vector3D Direction;

    Ray() = default;
    Ray(const Math::Point3D &origin, const Math::Vector3D &direction)
        : Origin(origin)
        , Direction(direction)
    {
    }
};

class Material {
public:
    Math::RGBA color;
    double refractionIndex;

    Material(const Math::RGBA &color, double refractionIndex = 1.0)
        : color(color)
        , refractionIndex(refractionIndex)
    {
    }

    virtual ~Material() = default;
};

class Flat : public Material {
public:
    Flat(const Math::RGBA &color, double refractionIndex = 1.0)
        : Material(color, refractionIndex)
    {
    }
};

class IShape {
public:
    virtual ~IShape()
    {
    }
    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const = 0;
};


class Sphere : public IShape {
public:
    Math::Point3D Center;
    double Radius;
    Math::RGBA Color;

    Sphere(const Math::Point3D &center, double radius, const Math::RGBA &color)
        : Center(center)
        , Radius(radius)
        , Color(color)
    {
    }

    virtual bool
    hits(const Ray &ray, Math::RGBA &hitColor, double &t) const override
    {
        Math::Vector3D oc = Center.getVectorTo(ray.Origin);
        double a = ray.Direction.dot(ray.Direction);
        double b = 2.0 * oc.dot(ray.Direction);
        double c = oc.dot(oc) - Radius * Radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        } else {
            double sqrtDiscriminant = std::sqrt(discriminant);
            double t1 = (-b - sqrtDiscriminant) / (2 * a);
            double t2 = (-b + sqrtDiscriminant) / (2 * a);

            t = t1 > 0 ? t1 : (t2 > 0 ? t2 : -1);
            if (t < 0)
                return false;

            hitColor = Color;
            return true;
        }
    }
};

class Rectangle3D {
public:
    Math::Point3D Origin;
    Math::Vector3D BottomSide;
    Math::Vector3D LeftSide;

    Rectangle3D(const Math::Point3D &origin,
                const Math::Vector3D &bottomSide,
                const Math::Vector3D &leftSide)
        : Origin(origin)
        , BottomSide(bottomSide)
        , LeftSide(leftSide)
    {
    }

    Math::Point3D pointAt(double u, double v) const
    {
        return Origin + BottomSide * u + LeftSide * v;
    }
};

class Camera {
public:
    Math::Point3D origin;

    Camera(const Math::Point3D &origin = Math::Point3D(0, 0, 1))
        : origin(origin)
    {
    }

    Ray ray(double u, double v) const
    {
        return Ray(origin, Math::Vector3D(u - 0.5, v - 0.5, -1).normalized());
    }

    Math::RGBA
    traceRay(const Ray &ray,
             const std::vector<std::unique_ptr<IShape>> &shapes) const
    {
        Math::RGBA closestColor = defaultColor;
        double minDist = std::numeric_limits<double>::infinity();

        for (const auto &shape : shapes) {
            double dist;
            Math::RGBA hitColor;
            if (shape->hits(ray, hitColor, dist) && dist < minDist) {
                minDist = dist;
                closestColor = hitColor;
            }
        }
        return closestColor;
    }

private:
    Math::RGBA defaultColor{0, 0, 0};
};

class Scene {
public:
    std::vector<std::unique_ptr<IShape>> shapes;
    Camera camera;
    int width, height;

    Scene(int w, int h) : width(w), height(h)
    {
    }

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    void addShape(std::unique_ptr<IShape> shape)
    {
        shapes.push_back(std::move(shape));
    }

    void setCamera(const Camera &cam)
    {
        camera = cam;
    }

    void generateImage(std::ostream &out) const
    {
        out << "P3\n" << width << ' ' << height << "\n255\n";

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                double u = double(x) / (width - 1);
                double v = double(y) / (height - 1);
                Ray r = camera.ray(u, v);
                Math::RGBA color = camera.traceRay(r, shapes);
                color.write_color(out);
            }
        }
    }
};

} // namespace RayTracer
