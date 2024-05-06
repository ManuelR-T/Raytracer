/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#pragma once
#include <exception>

namespace RayTracer {

    class ParsingValueNotFound : public std::exception
    {
        public:
            const char *what() const noexcept override;
    };
}
