/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "define.hpp"
#include "Shapes/Shapes.hpp"

#include <exception>
#include <fstream>
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
        return FAILURE;
    RayTracer::Scene scene(0,0,1);
    try {
        RayTracer::SceneParser parser(scene);
        std::ofstream file("image.ppm");

        parser.parseScene(av[1]);
        scene.generateImage(file);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
