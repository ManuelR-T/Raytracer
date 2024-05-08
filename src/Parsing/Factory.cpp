/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory
*/

#include "Factory.hpp"
#include "../Exception.hpp"
#include "ParseInformations.hpp"

#include <libconfig.h++>

const std::unordered_map<std::string, std::function<std::unique_ptr<RayTracer::IShape>(const libconfig::Setting &)>> RayTracer::Factory::m_FACTORY = {
        {"spheres", [] (const libconfig::Setting &item) {return createSphere(item); }},
        {"planes", [] (const libconfig::Setting &item) {return createPlane(item); }},
        {"cubes", [] (const libconfig::Setting &item) {return createCube(item);}},
        {"cones", [] (const libconfig::Setting &item) {return createCone(item);}}
};

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createCube(const libconfig::Setting &item)
{
    try {
        double r;
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");

        if (!(item.lookupValue("r", r)))
            throw RayTracer::ParsingValueNotFound();
        Vector3D pos = ParseInformations::getCoords(position);
        Vector3D vec = ParseInformations::getAxis(axis);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);
        return (std::make_unique<RayTracer::Cube>(
            pos,
            r,
            vec,
            ParseInformations::getMatColour(item)));
    } catch (std::exception &e) {
        return nullptr;
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createCone(const libconfig::Setting &item)
{
    try {
        double r;
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");

        if (!(item.lookupValue("r", r)))
            throw RayTracer::ParsingValueNotFound();
        Vector3D pos = ParseInformations::getCoords(position);
        Vector3D vec = ParseInformations::getAxis(axis);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);
        return (std::make_unique<RayTracer::Cones>(
            pos,
            ParseInformations::getMatColour(item),
            r,
            vec));
    } catch (std::exception &e) {
        return nullptr;
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createPlane(const libconfig::Setting &item)
{
    try {
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");
        Vector3D vec;

        vec = ParseInformations::getAxis(axis);
        Vector3D pos = ParseInformations::getCoords(position);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);
        return (std::make_unique<RayTracer::Plane>(
            ParseInformations::getCoords(position),
            vec,
            ParseInformations::getMatColour(item)));
    } catch (std::exception &e) {
        return nullptr;
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createSphere(const libconfig::Setting &item)
{
    try {
        double r;
        if (!item.lookupValue("r", r))
            throw RayTracer::ParsingValueNotFound();
        Vector3D vec = ParseInformations::getCoords(item);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, vec);
        return (std::make_unique<RayTracer::Sphere>(
            vec,
            r,
            ParseInformations::getMatColour(item)));
    } catch (std::exception &e) {
        return nullptr;
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createShape(const libconfig::Setting &item, const std::string &type)
{
    if (m_FACTORY.contains(type)) {
        return m_FACTORY.at(type)(item);
    }
    return nullptr;
}