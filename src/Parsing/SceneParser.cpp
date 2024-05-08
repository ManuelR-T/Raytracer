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
#include "RGBA.hpp"
#include "../Shapes/Shapes.hpp"

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
    int pos[3] = {0};

    if(!(position.lookupValue("x", pos[0])
        && position.lookupValue("y", pos[1])
        && position.lookupValue("z", pos[2])))
        throw RayTracer::ParsingValueNotFound();
    RayTracer::Camera cam(Point3D{
            static_cast<double>(pos[0]),
            static_cast<double>(pos[1]),
            static_cast<double>(pos[2])});
    m_scene.setCamera(cam);
}

Point3D RayTracer::SceneParser::getCoords(const libconfig::Setting &list)
{
    double pos[3];

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw RayTracer::ParsingValueNotFound();
    return Point3D{pos[0],pos[1],pos[2]};
}

Vector3D RayTracer::SceneParser::getAxis(const libconfig::Setting &list)
{
    double pos[3];

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw RayTracer::ParsingValueNotFound();
    return Vector3D{pos[0],pos[1],pos[2]};
}

Math::RGBA RayTracer::SceneParser::getColour(const libconfig::Setting &list)
{
    const libconfig::Setting &colours = list.lookup("color");
    int color[3];
    std::string str;

    if (!(colours.lookupValue("r", color[0])
        && colours.lookupValue("g", color[1])
        && colours.lookupValue("b", color[2])))
        throw RayTracer::ParsingValueNotFound();
    return Math::RGBA(color[0], color[1], color[2]);
}

RayTracer::Material RayTracer::SceneParser::getMatColour(const libconfig::Setting &list)
{
    const libconfig::Setting &colours = list.lookup("color");
    int color[3];
    std::string str;

    if (!(colours.lookupValue("r", color[0])
        && colours.lookupValue("g", color[1])
        && colours.lookupValue("b", color[2])
        && list.lookupValue("material", str)))
        throw RayTracer::ParsingValueNotFound();
    if (str == "Glassy")
        return RayTracer::Glassy(Math::RGBA(color[0], color[1], color[2]));
    if (str == "Flat")
        return RayTracer::Flat(Math::RGBA(color[0], color[1], color[2]));
    return Math::RGBA(color[0], color[1], color[2]);
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
            m_scene.addShape(std::make_unique<RayTracer::Sphere>(
                getCoords(spheres[i]),
                r,
                getMatColour(spheres[i])));
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
            vec = getAxis(axis);
            m_scene.addShape(std::make_unique<RayTracer::Plane>(
                getCoords(position),
                vec,
                getMatColour(planes[i])));
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
        double height;
        const int ctr = cones.getLength();

        for (int i = 0; i < ctr; i++) {
            const libconfig::Setting &position = cones[i].lookup("position");
            if (!(cones[i].lookupValue("r", r)))
                continue;
            if (!(cones[i].lookupValue("height", height)))
                continue;
            const libconfig::Setting &axis = cones[i].lookup("axis");
            m_scene.addShape(std::make_unique<RayTracer::LimitedCones>(
                getCoords(position),
                getMatColour(cones[i]),
                r,
                getAxis(axis),
                height));
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
                getCoords(cubes[i]),
                r,
                getMatColour(cubes[i])));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parsePrimitives(const libconfig::Setting &primitives)
{
    // int ctr = primitives.getLength();

    // for (int i = 0; i < ctr; i++) {
        parseSphere(primitives);
        parsePlanes(primitives);
        parseCones(primitives);
        parseCubes(primitives);
    // }
}

void RayTracer::SceneParser::getPointLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::PointLight>(
            getCoords(list[i]),
            getColour(list[i])));
    }
}

void RayTracer::SceneParser::getDirectionnalLight(const libconfig::Setting &list)
{
    int ctr = list.getLength();

    for (int i = 0; i < ctr; i++) {
        m_scene.addLight(std::make_unique<RayTracer::DirectionalLight>(
            getAxis(list[i]),
            getColour(list[i])));
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
        std::cerr << e.what() << std::endl;
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
