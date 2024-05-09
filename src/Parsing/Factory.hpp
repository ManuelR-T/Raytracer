/*
** EPITECH PROJECT, 2024
** 4
** File description:
** Factory
*/

#pragma once

#include <libconfig.h++>
#include "../Shapes/Shapes.hpp"
#include "Matrix/Matrix.hpp"
#include <memory>
#include <unordered_map>
#include <string>


namespace RayTracer {

    class Factory {
        public:
            Factory() = delete;
            ~Factory() = delete;
            static std::unique_ptr<RayTracer::IShape> createShape(const libconfig::Setting &item, const std::string &type, Vector3D &);
            static const std::unordered_map<std::string, std::function<std::unique_ptr<RayTracer::IShape>(const libconfig::Setting &, Vector3D &)>>m_FACTORY;

        private:
            static std::unique_ptr<RayTracer::IShape> createCube(const libconfig::Setting &item, Vector3D &);
            static std::unique_ptr<RayTracer::IShape> createSphere(const libconfig::Setting &item, Vector3D &);
            static std::unique_ptr<RayTracer::IShape> createPlane(const libconfig::Setting &item, Vector3D &);
            static std::unique_ptr<RayTracer::IShape> createCone(const libconfig::Setting &item, Vector3D &);
    };
}
