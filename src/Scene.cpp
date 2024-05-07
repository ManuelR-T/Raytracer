/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Shapes/IShape.hpp"

#include <memory>
#include <vector>

namespace RayTracer {

Scene::Scene(int w, int h, int fov) : width(w), height(h), fov(fov)
{
}

void Scene::addShape(std::unique_ptr<IShape> shape)
{
    shapes.push_back(std::move(shape));
}

void Scene::addLight(std::unique_ptr<ILight> light)
{
    lights.push_back(std::move(light));
}

void Scene::setCamera(const RayTracer::Camera &cam)
{
    camera = std::make_unique<Camera>(cam);
}

void Scene::generateImage(std::ostream &out) const
{
    out << "P3\n" << width << ' ' << height << "\n255\n";

    for (int y = height - 1; y >= 0; --y) {
        for (int x = width - 1; x >= 0; --x) {
            double u = double(x) / (width - 1);
            double v = double(y) / (height - 1);
            Ray r = camera->ray(u, v, fov, double(width) / height);
            Math::RGBA color = camera->traceRay(r, *this);
            color.write_color(out);
        }
    }
}
} // namespace RayTracer
