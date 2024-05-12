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
#include "RGBA.hpp"
#include <memory>

Math::RGBA RayTracer::ParseInformations::getColour(const libconfig::Setting &list)
{
    const libconfig::Setting &colours = list.lookup("color");
    std::array<int, 3> color;
    std::string str;

    if (!(colours.lookupValue("r", color[0])
        && colours.lookupValue("g", color[1])
        && colours.lookupValue("b", color[2])))
        throw Error::ParsingValueNotFound("color not found");
    return Math::RGBA(color[0], color[1], color[2]);
}

std::unique_ptr<RayTracer::Material> RayTracer::ParseInformations::getMatColour(const libconfig::Setting &list)
{
    const libconfig::Setting &rgb = list.lookup("color");
    std::array<int, 3> color;
    std::array<int, 3> color2;
    std::string str;

    if (!(rgb.lookupValue("r", color[0])
        && rgb.lookupValue("g", color[1])
        && rgb.lookupValue("b", color[2])
        && list.lookupValue("material", str)))
        throw Error::ParsingValueNotFound("color or material not found");
    if (str == "Glassy")
        return std::make_unique<RayTracer::Glassy>(Math::RGBA(color[0], color[1], color[2]));
    if (str == "Flat")
        return std::make_unique<RayTracer::Flat>(Math::RGBA(color[0], color[1], color[2]));
    const libconfig::Setting &rgb2 = list.lookup("color2");
    if (!(rgb2.lookupValue("r", color2[0])
        && rgb2.lookupValue("g", color2[1])
        && rgb2.lookupValue("b", color2[2])))
        throw Error::ParsingValueNotFound("color2 not found");
    double scale = 1.0;
    if (!list.lookupValue("scale", scale))
        throw Error::ParsingValueNotFound("scale not found");
    if (str == "ChessBoard")
        return std::make_unique<RayTracer::ChessBoard>(Math::RGBA(color[0], color[1], color[2]), Math::RGBA(color2[0], color2[1], color2[2]), scale);
    if (str == "Perlin")
        return std::make_unique<RayTracer::PerlinNoiseMaterial>(Math::RGBA(color[0], color[1], color[2]), Math::RGBA(color2[0], color2[1], color2[2]), scale);
    throw Error::ParsingValueNotFound("material not found");
}

Point3D RayTracer::ParseInformations::getCoords(const libconfig::Setting &list)
{
    std::array<double, 3> pos;

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw Error::ParsingValueNotFound("coords not found");
    return Point3D{pos[0],pos[1],pos[2]};
}

Vector3D RayTracer::ParseInformations::getAxis(const libconfig::Setting &list)
{
    std::array<double, 3> pos;

    if (!(list.lookupValue("x", pos[0])
        && list.lookupValue("y", pos[1])
        && list.lookupValue("z", pos[2])))
        throw Error::ParsingValueNotFound("axis not found");
    return Vector3D{pos[0],pos[1],pos[2]};
}

void RayTracer::ParseInformations::getRotation(const libconfig::Setting &item, Vector3D &pos)
{
    std::array<double, 3>angles = {0, 0, 0};
    if (!item.exists("rotation"))
        return;
    try {
        const libconfig::Setting &rotation = item.lookup("rotation");

        if (!(rotation.lookupValue("x", angles[0])
            && rotation.lookupValue("y", angles[1])
            && rotation.lookupValue("z", angles[2])))
            throw Error::ParsingValueNotFound("");
        if (angles[0])
            Math::Transformation3D::rotateX(pos, angles[0] * M_PI / 180);
        if (angles[1])
            Math::Transformation3D::rotateY(pos, angles[1] * M_PI / 180);
        if (angles[2])
            Math::Transformation3D::rotateZ(pos, angles[2] * M_PI / 180);
    } catch (std::exception &e) {
        throw Error::ParsingValueNotFound("rotation not found");
    }
}

void RayTracer::ParseInformations::getTranslation(const libconfig::Setting &item, Vector3D &pos)
{
    std::array<double, 3>move = {0};
    if (!item.exists("translation"))
        return;
    try {
        const libconfig::Setting &translation = item.lookup("translation");

    if (!(translation.lookupValue("x", move[0])
            && translation.lookupValue("y", move[1])
            && translation.lookupValue("z", move[2])))
            throw Error::ParsingValueNotFound("translation not found");
        Math::Transformation3D::translate(pos, Vector3D{move[0], move[1], move[2]});
    } catch (std::exception &e) {
        throw Error::ParsingValueNotFound("translation not found");
    }
}

