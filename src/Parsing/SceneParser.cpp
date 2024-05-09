/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include "../Error/Exception.hpp"
#include "../Camera.hpp"
#include "../Lights.hpp"
#include "Matrix/Matrix.hpp"
#include "ParseInformations.hpp"
#include "Factory.hpp"

#include <array>
#include <exception>
#include <libconfig.h++>
#include <memory>

RayTracer::SceneParser::SceneParser(RayTracer::Scene &scene, Vector3D &vec) : m_scene(scene), m_offset(vec)
{
}

void RayTracer::SceneParser::parseCamera(const libconfig::Setting &camera)
{
    const libconfig::Setting &position = camera[1];
    std::array<double, 3> pos{0, 0, 0};

    if(!(position.lookupValue("x", pos[0])
        && position.lookupValue("y", pos[1])
        && position.lookupValue("z", pos[2])))
        throw Error::ParsingValueNotFound("");
    Vector3D vec = Vector3D{pos[0], pos[1], pos[2]};
    RayTracer::Camera cam(vec);
    ParseInformations::getRotation(camera, cam.direction);
    ParseInformations::getTranslation(camera, cam.origin);
    m_scene.setCamera(cam);
}

void RayTracer::SceneParser::parseItem(const libconfig::Setting &primitives, const std::string &str)
{
    try {
        const libconfig::Setting &item = primitives.lookup(str);
        const int ctr = item.getLength();

        for (int i = 0; i < ctr; i++) {
            m_scene.addShape(Factory::createShape(item[i], str, m_offset));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parsePrimitives(const libconfig::Setting &primitives)
{
    parseItem(primitives, "spheres");
    parseItem(primitives, "cones");
    parseItem(primitives, "planes");
    parseItem(primitives, "cubes");
}

void RayTracer::SceneParser::getPointLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::PointLight>(
            ParseInformations::getCoords(list[i]) + m_offset,
            ParseInformations::getColour(list[i])));
    }
}

void RayTracer::SceneParser::getDirectionnalLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::DirectionalLight>(
            ParseInformations::getAxis(list[i]) + m_offset,
            ParseInformations::getColour(list[i])));
    }
}

void RayTracer::SceneParser::parseLights(const libconfig::Setting &lights)
{
    try {
        const libconfig::Setting &point_lights = lights.lookup("point");
        getPointLight(point_lights);

        const libconfig::Setting &directional_lights = lights.lookup("directional");
        getDirectionnalLight(directional_lights);
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::getScene(const libconfig::Setting &scene)
{
    try {
        std::string file;
        std::array<double, 3> pos;

        if (!scene.lookupValue("filename", file))
            throw Error::ParsingValueNotFound("");
        const libconfig::Setting &off = scene.lookup("offset");
        if(!(off.lookupValue("x", pos[0])
        && off.lookupValue("y", pos[1])
        && off.lookupValue("z", pos[2])))
            throw Error::ParsingValueNotFound("");
        m_offset = Vector3D{pos[0], pos[1], pos[2]};
        parseScene(file, true);
    } catch (std::exception &e) {
        return;
    }
}

RayTracer::Scene &RayTracer::SceneParser::parseScene(const std::string &filename, const bool imported)
{
    libconfig::Config conf;

    try {
        conf.readFile(filename.c_str());
        const libconfig::Setting &root = conf.getRoot();
        if (!imported) {
            const libconfig::Setting &camera = root.lookup("camera");

            if (!(camera[0].lookupValue("width", m_scene.width)
                && camera[0].lookupValue("height", m_scene.height)
                && camera.lookupValue("fieldOfView", m_scene.fov)))
                throw Error::ParsingValueNotFound("Missing mandatory values for scene.");
            parseCamera(camera);
        }
        const libconfig::Setting &primitives = root.lookup("primitives");
        parsePrimitives(primitives);
        const libconfig::Setting &lights = root.lookup("lights");
        parseLights(lights);
        const libconfig::Setting &scene = root.lookup("scene");
        getScene(scene);
        return m_scene;
    } catch (std::exception &e) {
        return m_scene;
    }
}
