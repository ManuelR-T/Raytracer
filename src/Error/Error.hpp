/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Error
*/

#include <exception>
#include <string>

namespace Error {
    class Error : public std::exception {
    public:
        Error(const std::string &errType): m_errType(errType) {}

    protected:
        std::string const where() const noexcept { return m_errType; }

        std::string m_errType;
    };
}