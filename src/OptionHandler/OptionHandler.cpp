/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** OptionHandler
*/

#include "OptionHandler.hpp"

const std::array<std::string, 4> RayTracer::OptionHandler::formatSupported = {
    "png",
    "jpg",
    "tga",
    "bmp"
};

void RayTracer::OptionHandler::parseOption(int ac, char const **av, int &i)
{
    std::string args(av[i]);

    if (args == "--format") {
        if (i + 1 == ac) {
            throw Error::OptionHandlerError("Flag with empty parameter.");
        }
        std::string val(av[i + 1]);
        bool found = false;
        for (const auto &format: formatSupported) {
            if (format == val) {
                found = true;
            }
        }
        if (!found) {
            throw Error::OptionHandlerError("Format is not supported or invalid.");
        }
        this->m_format = val;
        i++;
        return;
    }
    throw Error::OptionHandlerError("Unsupported flag.");
}

void RayTracer::OptionHandler::commandLineParser(int ac, char const **av)
{
    bool sceneFound = false;

    for (int i = 1; i < ac; i++) {
        if (av[i][0] == '-') {
            parseOption(ac, av, i);
        } else {
            if (sceneFound) {
                throw Error::OptionHandlerError("Scene has already been found.");
            }
            sceneFound = true;
            this->m_scenePath = av[i];
        }
    }
    if (!this->m_scenePath.length()) {
        throw Error::OptionHandlerError("No scene provided.");
    }
}
