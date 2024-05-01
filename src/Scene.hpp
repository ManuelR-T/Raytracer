/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#pragma once

#include "Camera.hpp"

#include <memory>
#include <vector>

namespace RayTracer {
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
