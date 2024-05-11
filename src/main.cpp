/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Matrix/Matrix.hpp"
#include "OptionHandler/OptionHandler.hpp"
#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "define.hpp"

#include <exception>
#include <iostream>

int main(int ac, char **av)
{
    RayTracer::Scene scene(0,0,1);
    Vector3D vec{0,0,0};
    try {
        RayTracer::OptionHandler op;
        op.commandLineParser(ac, (const char **) av);
        RayTracer::SceneParser parser(scene, vec);

        parser.parseScene(op.getScenePath(), false);
        scene.loopImage(op.getFormat());
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
