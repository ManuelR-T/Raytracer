/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneParser
*/

#include "SceneParser.hpp"
#include "Exception.hpp"
#include "Matrix/Matrix.hpp"
#include "Camera.hpp"
#include "Lights.hpp"
#include "Materials/Glassy.hpp"
#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "Shapes/Sphere.hpp"
#include "define.hpp"

#include "Materials/Materials.hpp"
#include "Shapes/Shapes.hpp"
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

void RayTracer::SceneParser::parseSphere(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &spheres = primitives.lookup("spheres");
        int pos[4];
        int color[3];
        const int ctr = spheres.getLength();

        for (int i = 0; i < ctr; i++) {
            if (!(spheres[i].lookupValue("x", pos[0])
                && spheres[i].lookupValue("y", pos[1])
                && spheres[i].lookupValue("z", pos[2])
                && spheres[i].lookupValue("r", pos[3])))
                continue;
            const libconfig::Setting &colours = spheres[i].lookup("color");
                if (!(colours.lookupValue("r", color[0])
                    && colours.lookupValue("g", color[1])
                    && colours.lookupValue("b", color[2])))
                    continue;
            m_scene.addShape(std::make_unique<RayTracer::Sphere>(
                Point3D{
                    static_cast<double>(pos[0]),
                    static_cast<double>(pos[1]),
                    static_cast<double>(pos[2])},
                pos[3],
                Math::RGBA(
                    static_cast<double>(color[0]),
                    static_cast<double>(color[1]),
                    static_cast<double>(color[2]))));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parsePlanes(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &planes = primitives.lookup("planes");
        int pos[3];
        int axe[3];
        int color[3];
        const int ctr = planes.getLength();

        for (int i = 0; i < ctr; i++) {
            const libconfig::Setting &axis = planes[i].lookup("axis");
            if (!(axis.lookupValue("x", axe[0])
                && axis.lookupValue("y", axe[1])
                && axis.lookupValue("z", axe[2])))
                continue;
            const libconfig::Setting &position = planes[i].lookup("position");
            if (!(position.lookupValue("x", pos[0])
                && position.lookupValue("y", pos[1])
                && position.lookupValue("z", pos[2])))
                continue;
            const libconfig::Setting &colours = planes[i].lookup("color");
                if (!(colours.lookupValue("r", color[0])
                    && colours.lookupValue("g", color[1])
                    && colours.lookupValue("b", color[2])))
                    continue;
            m_scene.addShape(std::make_unique<RayTracer::Plane>(
                Point3D{
                    static_cast<double>(axe[0]),
                    static_cast<double>(axe[1]),
                    static_cast<double>(axe[2])},
                Vector3D{
                    static_cast<double>(pos[0]),
                    static_cast<double>(pos[1]),
                    static_cast<double>(pos[2])},
                Math::RGBA(
                    static_cast<double>(color[0]),
                    static_cast<double>(color[1]),
                    static_cast<double>(color[2]))));
        }
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::SceneParser::parseCones(const libconfig::Setting &primitives)
{
    try {
        const libconfig::Setting &cones = primitives.lookup("cones");
        int pos[4];
        int axe[3];
        int color[3];
        const int ctr = cones.getLength();

        for (int i = 0; i < ctr; i++) {
            const libconfig::Setting &position = cones[i].lookup("position");
            if (!(position.lookupValue("x", pos[0])
                && position.lookupValue("y", pos[1])
                && position.lookupValue("z", pos[2])
                && cones[i].lookupValue("r", pos[3])))
                continue;
            const libconfig::Setting &colours = cones[i].lookup("color");
                if (!(colours.lookupValue("r", color[0])
                    && colours.lookupValue("g", color[1])
                    && colours.lookupValue("b", color[2])))
                    continue;
            const libconfig::Setting &axis = cones[i].lookup("axis");
            if (!(axis.lookupValue("x", axe[0])
                && axis.lookupValue("y", axe[1])
                && axis.lookupValue("z", axe[2])))
                continue;
            m_scene.addShape(std::make_unique<RayTracer::Cones>(
                Point3D{
                    static_cast<double>(pos[0]),
                    static_cast<double>(pos[1]),
                    static_cast<double>(pos[2])},
                Math::RGBA(
                    static_cast<double>(color[0]),
                    static_cast<double>(color[1]),
                    static_cast<double>(color[2])),
                pos[3],
                Vector3D{
                    static_cast<double>(pos[0]),
                    static_cast<double>(pos[1]),
                    static_cast<double>(pos[2])}
                ));
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
    }
}

void RayTracer::SceneParser::parseLights(const libconfig::Setting &lights)
{
    try {
        const libconfig::Setting &point_lights = lights.lookup("point");
        getLightCoords<RayTracer::PointLight>(point_lights);

        const libconfig::Setting &directional_lights = lights.lookup("directional");
        getLightCoords<RayTracer::DirectionalLight>(directional_lights);
    } catch (libconfig::SettingNotFoundException &e) {
        return;
    }
}

RayTracer::Scene &RayTracer::SceneParser::parseScene(const std::string &filename)
{
    libconfig::Config conf;

    try {
        conf.readFile(filename);
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
