/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Shapes/IShape.hpp"

#include <climits>
#include <memory>
#include <vector>

namespace RayTracer {
std::vector<std::unique_ptr<IShape>> shapes;
std::vector<std::unique_ptr<ILight>> lights;
std::unique_ptr<Camera> camera;
int width, height;

Scene::Scene(int w, int h) : width(w), height(h)
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
            Ray r = camera->ray(u, v);
            Math::RGBA color = camera->traceRay(r, *this);
            color.write_color(out);
        }
    }
}
} // namespace RayTracer
