/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Matrix/Matrix.hpp"
#include "Parsing/SceneParser.hpp"
#include "Scene.hpp"
#include "define.hpp"

#include <exception>
#include <fstream>
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
        return FAILURE;
    RayTracer::Scene scene(0,0,1);
    Vector3D vec{0,0,0};
    try {
        RayTracer::SceneParser parser(scene, vec);
        std::ofstream file("image.ppm");

        parser.parseScene(av[1], false);
        // scene.generateImage(file);
        scene.loopImage();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
