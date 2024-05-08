/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneParser
*/

#pragma once
#include "../Scene.hpp"
#include "../Shapes/Shapes.hpp"
#include <libconfig.h++>

namespace RayTracer {

    class SceneParser {
        public:
            SceneParser() = delete;
            SceneParser(RayTracer::Scene &);
            ~SceneParser() = default;
            RayTracer::Scene &parseScene(const std::string &file);
        private:
            void getPointLight(const libconfig::Setting &list);
            void getDirectionnalLight(const libconfig::Setting &list);
            void parseCamera(const libconfig::Setting &);
            void parsePrimitives(const libconfig::Setting &);
            void parseLights(const libconfig::Setting &);
            void parsePlanes(const libconfig::Setting &);
            void parseSphere(const libconfig::Setting &);
            void parseCubes(const libconfig::Setting &);
            void parseCones(const libconfig::Setting &);

            RayTracer::Scene &m_scene;
    };
}
