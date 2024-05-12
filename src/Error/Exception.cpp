/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#include "Exception.hpp"

const char *Error::ParsingValueNotFound::what() const noexcept
{
    return m_errMsg.c_str();
}