/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Raytracer
*/

#pragma once

#include "Materials/Material.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include "Camera.hpp"

namespace RayTracer {

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

class Scene {
public:
    std::vector<std::unique_ptr<IObject>> shapes;
    Camera camera;
    int width, height;

    Scene(int w, int h) : width(w), height(h)
    {
    }

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    void addShape(std::unique_ptr<IObject> shape)
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
