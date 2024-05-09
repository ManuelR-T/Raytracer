/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#pragma once

#include "Error.hpp"

namespace Error {

    class ParsingValueNotFound : public Error
    {
    public:
        ParsingValueNotFound(const std::string &errMsg):
            Error("[ValueNotFound]: "),
            m_errMsg(errMsg)
        {}

        const char *what() const noexcept override;
    private:
        std::string m_errMsg;
    };
}
