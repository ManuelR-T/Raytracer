/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#include "Exception.hpp"

const char *RayTracer::ParsingValueNotFound::what() const noexcept
{
    return _message.c_str();
}