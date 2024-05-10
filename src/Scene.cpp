/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Shapes/IShape.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <memory>
#include <vector>

namespace RayTracer {

Scene::Scene(int w, int h, int fov):
    width(w),
    height(h),
    fov(fov),
    m_image(),
    m_win()
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

void Scene::generateImage(bool isLight)
{
    for (int y = height - 1; y >= 0; --y) {
        for (int x = width - 1; x >= 0; --x) {
            double u = double(x) / (width - 1);
            double v = double(y) / (height - 1);
            Ray r = camera->ray(u, v, fov, double(width) / height);
            Math::RGBA color = camera->traceRay(r, *this, isLight);
            m_image.setPixel(width - x - 1, height - y - 1, {color.R, color.G, color.B, color.A});
        }
    }
}

void Scene::loopImage()
{
    m_image.create(width, height);
    generateImage(true);

    sf::Texture texture;
    texture.loadFromImage(m_image);
    sf::Sprite sImage(texture);

    m_win.create(sf::VideoMode(width, height), "RayTracer");
    while (m_win.isOpen()) {
        m_win.clear(sf::Color{0, 0, 0});
        m_win.draw(sImage);
        sf::Event ev;
        if (m_win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                m_win.close();
            }
        }
        m_win.display();
    }
    m_image.saveToFile("image.png");
}

} // namespace RayTracer
