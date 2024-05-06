/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Camera.hpp"
#include "Lights.hpp"
#include "Materials/Glassy.hpp"
#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "define.hpp"

#include "Materials/Materials.hpp"
#include "Transformations/Transformation.hpp"
#include "Shapes/Shapes.hpp"

#include <exception>
#include <iostream>
#include <cmath>

int main(int ac, char **av)
{
    if (ac != 2)
        return FAILURE;
    RayTracer::Scene scene(0,0);
    try {
        RayTracer::SceneParser parser(scene);
        parser.parseScene(av[1]);
        scene.generateImage(std::cout);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
