/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Factory
*/

#include "Factory.hpp"
#include "../Error/Exception.hpp"
#include "Matrix/Matrix.hpp"
#include "ParseInformations.hpp"

#include <libconfig.h++>

const std::unordered_map<std::string, std::function<std::unique_ptr<RayTracer::IShape>(const libconfig::Setting &, Vector3D &)>> RayTracer::Factory::m_FACTORY = {
        {"spheres", [] (const libconfig::Setting &item, Vector3D &vec) {return createSphere(item, vec); }},
        {"planes", [] (const libconfig::Setting &item, Vector3D &vec) {return createPlane(item, vec); }},
        {"cubes", [] (const libconfig::Setting &item, Vector3D &vec) {return createCube(item, vec);}},
        {"cones", [] (const libconfig::Setting &item, Vector3D &vec) {return createCone(item, vec);}}
};

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createCube(const libconfig::Setting &item, Vector3D &offset)
{
    try {
        double r;
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");

        if (!(item.lookupValue("r", r)))
            throw Error::ParsingValueNotFound("");
        Vector3D pos = ParseInformations::getCoords(position) + offset;
        Vector3D vec = ParseInformations::getAxis(axis);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);
        return (std::make_unique<RayTracer::Cube>(
            pos,
            r,
            vec,
            ParseInformations::getMatColour(item)));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw Error::ParsingValueNotFound("Cube Error");
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createCone(const libconfig::Setting &item, Vector3D &offset)
{
    try {
        double r;
        double height;
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");
        if (!(item.lookupValue("r", r)))
            throw Error::ParsingValueNotFound("");
        if (!(item.lookupValue("height", height)))
            throw Error::ParsingValueNotFound("");
        Vector3D pos = ParseInformations::getCoords(position) + offset;
        Vector3D vec = ParseInformations::getAxis(axis);
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);
        if (!(item.lookupValue("height", height)))
            return (std::make_unique<RayTracer::Cones>(
            pos,
            ParseInformations::getMatColour(item),
            r,
            vec));
        return (std::make_unique<RayTracer::LimitedCones>(
            pos,
            ParseInformations::getMatColour(item),
            r,
            vec.normalized()));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createPlane(const libconfig::Setting &item, Vector3D &offset)
{
    try {
        const libconfig::Setting &position = item.lookup("position");
        const libconfig::Setting &axis = item.lookup("axis");
        Vector3D vec = ParseInformations::getAxis(axis);
        Vector3D pos = ParseInformations::getCoords(position) + offset;
        ParseInformations::getRotation(item, vec);
        ParseInformations::getTranslation(item, pos);

        auto material = ParseInformations::getMatColour(item);
        return std::make_unique<RayTracer::Plane>(
            pos,
            vec,
            material);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}


std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createSphere(const libconfig::Setting &item, Vector3D &offset)
{
    std::cout << "Creating sphere" << std::endl;
    try {
        double r;
        if (!item.lookupValue("r", r))
            throw Error::ParsingValueNotFound("");
        Vector3D pos = ParseInformations::getCoords(item) + offset;
        ParseInformations::getRotation(item, pos);
        ParseInformations::getTranslation(item, pos);
        return std::make_unique<RayTracer::Sphere>(pos, r, ParseInformations::getMatColour(item));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return nullptr;
    }
}


std::unique_ptr<RayTracer::IShape> RayTracer::Factory::createShape(const libconfig::Setting &item, const std::string &type, Vector3D &vec)
{
    if (m_FACTORY.contains(type)) {
        return m_FACTORY.at(type)(item, vec);
    }
    return nullptr;
}