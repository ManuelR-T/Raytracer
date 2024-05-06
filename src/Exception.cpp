/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#include "Exception.hpp"

const char *RayTracer::ParsingValueNotFound::what() const noexcept
{
    const char *error = "Error finding value while parsing";

    return error;
}