/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include "../Exception.hpp"
#include "../Camera.hpp"
#include "../Lights.hpp"
#include "../Parsing/SceneParser.hpp"
#include "Matrix/Matrix.hpp"
#include "ParseInformations.hpp"
#include "../Shapes/Shapes.hpp"

#include <array>
#include <exception>
#include <iostream>
#include <libconfig.h++>
#include <memory>

RayTracer::SceneParser::SceneParser(RayTracer::Scene &scene) : m_scene(scene)
{
}

void RayTracer::SceneParser::parseCamera(const libconfig::Setting &camera)
{
    const libconfig::Setting &position = camera[1];
    std::array<double, 3> pos;

    if(!(position.lookupValue("x", pos[0])
        && position.lookupValue("y", pos[1])
        && position.lookupValue("z", pos[2])))
        throw RayTracer::ParsingValueNotFound();
    Vector3D vec = Vector3D{pos[0], pos[1], pos[2]};
    RayTracer::Camera cam(vec);
    ParseInformations::getRotation(camera, cam.direction);
    ParseInformations::getTranslation(camera, cam.origin);
    m_scene.setCamera(cam);
}

void RayTracer::SceneParser::parseSphere(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &spheres = primitives.lookup("spheres");
        double r;
        const int ctr = spheres.getLength();

        for (int i = 0; i < ctr; i++) {
            if (!spheres[i].lookupValue("r", r))
                continue;
            Vector3D vec = ParseInformations::getCoords(spheres[i]);
            ParseInformations::getTranslation(spheres[i], vec);
            m_scene.addShape(std::make_unique<RayTracer::Sphere>(
                vec,
                r,
                ParseInformations::getMatColour(spheres[i])));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parsePlanes(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &planes = primitives.lookup("planes");
        Vector3D vec;
        const int ctr = planes.getLength();

        for (int i = 0; i < ctr; i++) {
            const libconfig::Setting &position = planes[i].lookup("position");
            const libconfig::Setting &axis = planes[i].lookup("axis");
            vec = ParseInformations::getAxis(axis);
            Vector3D pos = ParseInformations::getCoords(position);
            ParseInformations::getTranslation(planes[i], pos);
            m_scene.addShape(std::make_unique<RayTracer::Plane>(
                pos,
                vec,
                ParseInformations::getMatColour(planes[i])));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parseCones(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &cones = primitives.lookup("cones");
        double r;
        const int ctr = cones.getLength();

        for (int i = 0; i < ctr; i++) {
            const libconfig::Setting &position = cones[i].lookup("position");
            if (!(cones[i].lookupValue("r", r)))
                continue;
            const libconfig::Setting &axis = cones[i].lookup("axis");
            Vector3D vec = ParseInformations::getCoords(position[i]);
            ParseInformations::getTranslation(cones[i], vec);
            m_scene.addShape(std::make_unique<RayTracer::Cones>(
                vec,
                ParseInformations::getMatColour(cones[i]),
                r,
                ParseInformations::getAxis(axis)));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parseCubes(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &cubes = primitives.lookup("cubes");
        double r;
        const int ctr = cubes.getLength();

        for (int i = 0; i < ctr; i++) {
            if (!(cubes[i].lookupValue("r", r)))
                continue;
            m_scene.addShape(std::make_unique<RayTracer::Cube>(
                ParseInformations::getCoords(cubes[i]),
                r,
                ParseInformations::getMatColour(cubes[i])));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parsePrimitives(const libconfig::Setting &primitives)
{
    int ctr = primitives.getLength();

    for (int i = 0; i < ctr; i++) {
        parseSphere(primitives);
        parsePlanes(primitives);
        parseCones(primitives);
        parseCubes(primitives);
    }
}

void RayTracer::SceneParser::getPointLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::PointLight>(
            ParseInformations::getCoords(list[i]),
            ParseInformations::getColour(list[i])));
    }
}

void RayTracer::SceneParser::getDirectionnalLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::DirectionalLight>(
            ParseInformations::getAxis(list[i]),
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

RayTracer::Scene &RayTracer::SceneParser::parseScene(const std::string &filename)
{
    libconfig::Config conf;

    try {
        conf.readFile(filename.c_str());
        const libconfig::Setting &root = conf.getRoot();
        const libconfig::Setting &camera = root.lookup("camera");

        if (!(camera[0].lookupValue("width", m_scene.width)
            && camera[0].lookupValue("height", m_scene.height)
            && camera.lookupValue("fieldOfView", m_scene.fov)))
            throw RayTracer::ParsingValueNotFound();
        parseCamera(camera);
        const libconfig::Setting &primitives = root.lookup("primitives");
        parsePrimitives(primitives);
        const libconfig::Setting &lights = root.lookup("lights");
        parseLights(lights);
        return m_scene;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return m_scene;
    }
}
