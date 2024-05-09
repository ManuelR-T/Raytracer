/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#include "Exception.hpp"

const char *Error::ParsingValueNotFound::what() const noexcept
{
    std::string mess = this->where() + m_errMsg;
    return mess.c_str();
}