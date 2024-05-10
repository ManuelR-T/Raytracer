/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ParseInformations
*/

#pragma once

#include "../Materials/Materials.hpp"
#include "Matrix/Matrix.hpp"
#include <libconfig.h++>

namespace RayTracer {
    class ParseInformations {
        public:
            static Math::RGBA getColour(const libconfig::Setting &list);
            static RayTracer::Material getMatColour(const libconfig::Setting &list);
            static Point3D getAxis(const libconfig::Setting &list);
            static Vector3D getCoords(const libconfig::Setting &list);
            static void getRotation(const libconfig::Setting &item, Vector3D &pos);
            static void getTranslation(const libconfig::Setting &item, Vector3D &pos);
            static void getShear(const libconfig::Setting &item, Vector3D &pos);
            static void getScale(const libconfig::Setting &item, Vector3D &pos);
    };
}