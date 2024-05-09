/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ParseInformations
*/

#include "ParseInformations.hpp"
#include "../Error/Exception.hpp"
#include "Matrix/Matrix.hpp"
#include "../Transformations/Transformation.hpp"

#include <cstdio>
#include <exception>

Math::RGBA RayTracer::ParseInformations::getColour(const libconfig::Setting &list)
{
    const libconfig::Setting &colours = list.lookup("color");
    std::array<int, 3> color;
    std::string str;

    if (!(colours.lookupValue("r", color[0])
        && colours.lookupValue("g", color[1])
        && colours.lookupValue("b", color[2])))
        throw Error::ParsingValueNotFound("");
    return Math::RGBA(color[0], color[1], color[2]);
}

RayTracer::Material RayTracer::ParseInformations::getMatColour(const libconfig::Setting &list)
{
    const libconfig::Setting &colours = list.lookup("color");
    std::array<int, 3> color;
    std::string str;

    if (!(colours.lookupValue("r", color[0])
        && colours.lookupValue("g", color[1])
        && colours.lookupValue("b", color[2])
        && list.lookupValue("material", str)))
        throw Error::ParsingValueNotFound("");
    if (str == "Glassy")
        return RayTracer::Glassy(Math::RGBA(color[0], color[1], color[2]));
    if (str == "Flat")
        return RayTracer::Flat(Math::RGBA(color[0], color[1], color[2]));
    return Math::RGBA(color[0], color[1], color[2]);
}

Point3D RayTracer::ParseInformations::getCoords(const libconfig::Setting &list)
{
    std::array<double, 3> pos;

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw Error::ParsingValueNotFound("");
    return Point3D{pos[0],pos[1],pos[2]};
}

Vector3D RayTracer::ParseInformations::getAxis(const libconfig::Setting &list)
{
    std::array<double, 3> pos;

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw Error::ParsingValueNotFound("");
    return Vector3D{pos[0],pos[1],pos[2]};
}

void RayTracer::ParseInformations::getRotation(const libconfig::Setting &item, Vector3D &pos)
{
    std::array<double, 3>angles = {0};
    try {
        const libconfig::Setting &rotation = item.lookup("rotation");

        if (!(rotation.lookupValue("x", angles[0])
            && rotation.lookupValue("y", angles[1])
            && rotation.lookupValue("z", angles[2])))
            throw Error::ParsingValueNotFound("");
        Math::Transformation3D::rotateX(pos, angles[0] * M_PI / 180);
        Math::Transformation3D::rotateY(pos, angles[1] * M_PI / 180);
        Math::Transformation3D::rotateZ(pos, angles[2] * M_PI / 180);
    } catch (std::exception &e) {
        return;
    }
}

void RayTracer::ParseInformations::getTranslation(const libconfig::Setting &item, Vector3D &pos)
{
    std::array<double, 3>move = {0};

    try {
        const libconfig::Setting &translation = item.lookup("translation");

    if (!(translation.lookupValue("x", move[0])
            && translation.lookupValue("y", move[1])
            && translation.lookupValue("z", move[2])))
            throw Error::ParsingValueNotFound("");
        Math::Transformation3D::translate(pos, Vector3D{move[0], move[1], move[2]});
    } catch (std::exception &e) {
        return;
    }
}

