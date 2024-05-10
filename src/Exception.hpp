/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** Exception
*/

#pragma once
#include <exception>
#include <string>

namespace RayTracer {

    class ParsingValueNotFound : public std::exception
    {
        public:
            ParsingValueNotFound(std::string const &message = "")
            {
                _message = "Error While Parsing" + message;
            }
            const char *what() const noexcept override;
        private:
            std::string _message;
    };
}
