/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include "Lights.hpp"
#include "Shapes/IShape.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstddef>
#include <memory>
#include <mutex>
#include <thread>
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

void Scene::generateLine(
    bool isLight,
    Scene &scene,
    int &y,
    std::mutex &mut
)
{
    auto &image = scene.getImage();
    int curr_y = y;

    for (int x = scene.width - 1; x >= 0; --x) {
        double u = double(x) / (scene.width - 1);
        double v = double(curr_y) / (scene.height - 1);
        Ray r = scene.camera->ray(u, v, scene.fov, double(scene.width) / scene.height);
        Math::RGBA color = scene.camera->traceRay(r, scene, isLight);
        image.setPixel(
            scene.width - x - 1,
            scene.height - curr_y - 1,
            {color.R, color.G, color.B, color.A}
        );
    }
    mut.lock();
    y--;
    if (y > 0) {
        mut.unlock();
        generateLine(isLight, scene, y, mut);
        return;
    }
    mut.unlock();
}

void Scene::generateImage(bool isLight, Scene &scene, size_t nbCpus)
{
    int y = scene.height - 1;
    std::vector<std::thread> v_threads;
    std::mutex mut;

    mut.lock();
    for (size_t i = 0; i < nbCpus; i++) {
        v_threads.push_back(std::thread(
            generateLine, isLight, std::ref(scene), std::ref(y), std::ref(mut))
        );
    }
    mut.unlock();
    for (auto &thread: v_threads) {
        thread.join();
    }
}

void Scene::loopImage(const std::string &format)
{
    m_image.create(width, height);

    size_t nbCpu = std::thread::hardware_concurrency();
    std::thread th(generateImage, true, std::ref(*this), nbCpu - 1);

    m_win.create(sf::VideoMode(width, height), "RayTracer");
    while (m_win.isOpen()) {
        m_win.clear(sf::Color{0, 0, 0});
        sf::Texture texture;
        texture.loadFromImage(m_image);
        sf::Sprite sImage(texture);
        m_win.draw(sImage);

        sf::Event ev;
        if (m_win.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                m_win.close();
            }
        }
        m_win.display();
    }
    th.join();
    if (format.length())
        m_image.saveToFile("image." + format);
}

} // namespace RayTracer
