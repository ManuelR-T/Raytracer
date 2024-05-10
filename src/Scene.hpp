/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene
*/

#pragma once

#include "Camera.hpp"
#include "Lights.hpp"
#include "Shapes/IShape.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

namespace RayTracer {
class Camera;
class Scene {
public:
    std::vector<std::unique_ptr<IShape>> shapes;
    std::vector<std::unique_ptr<ILight>> lights;
    std::unique_ptr<Camera> camera;
    int width, height, fov;
    Math::RGBA ambientLight{20, 20, 20};

    Scene(int w, int h, int fov);
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    void addShape(std::unique_ptr<IShape> shape);
    void addLight(std::unique_ptr<ILight> light);
    void setCamera(const RayTracer::Camera &cam);

    static void generateImage(bool isLight, Scene &scene, size_t nbCpus);

    void loopImage();

    [[nodiscard]] sf::Image &getImage() { return m_image; }

    private:

    static void generateLine(bool isLight, Scene &scene, int &y, std::mutex &mut);

    sf::Image m_image;
    sf::RenderWindow m_win;
};
} // namespace RayTracer
