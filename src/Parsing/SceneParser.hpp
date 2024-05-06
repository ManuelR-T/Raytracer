/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** SceneParser
*/

#pragma once
#include "Scene.hpp"
#include <libconfig.h++>
#include <memory>
#include <string>

namespace RayTracer {

    class SceneParser {
        public:
            SceneParser() = delete;
            SceneParser(RayTracer::Scene &);
            ~SceneParser() = default;
            RayTracer::Scene &parseScene(const std::string &file);
        private:
            template<typename T>
            void getLightCoords(const libconfig::Setting &list)
            {
                int pos[3];
                int color[3];
                int ctr = list.getLength();

                for (int i = 0; i < ctr; i++) {
                    if (!(list[i].lookupValue("x", pos[0])
                        && list[i].lookupValue("y", pos[1])
                        && list[i].lookupValue("z", pos[2])))
                        continue;
                const libconfig::Setting &colours = list[i].lookup("color");
                if (!(colours.lookupValue("r", color[0])
                    && colours.lookupValue("g", color[1])
                    && colours.lookupValue("b", color[2])))
                    continue;
                m_scene.addLight(std::make_unique<T>(
                    Point3D{
                        static_cast<double>(pos[0]),
                        static_cast<double>(pos[1]),
                        static_cast<double>(pos[2])},
                    Math::RGBA(
                        static_cast<double>(color[0]),
                        static_cast<double>(color[1]),
                        static_cast<double>(color[2]))));
                }
            }
            void parseCamera(const libconfig::Setting &);
            void parsePrimitives(const libconfig::Setting &);
            void parseLights(const libconfig::Setting &);
            void parseSphere(const libconfig::Setting &);
            void parsePlanes(const libconfig::Setting &);
            void parseCones(const libconfig::Setting &);

            RayTracer::Scene &m_scene;
    };
}
