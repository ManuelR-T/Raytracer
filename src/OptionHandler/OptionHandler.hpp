/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** ArgParser
*/

#pragma once

#include <string>
#include <array>

#include "../Error/Error.hpp"

namespace Error {
    class OptionHandlerError : public Error {
    public:
        OptionHandlerError(const std::string &errMsg):
            Error("[OptionError]: "),
            m_errMsg(errMsg)
        {
            std::string m_errMsg = this->where() + errMsg;
        }

        const char *what() const noexcept override { return m_errMsg.c_str(); }
    private:
        std::string m_errMsg;
    };
}

namespace RayTracer {
    class OptionHandler {
    public:
        OptionHandler() = default;

        ~OptionHandler() = default;

        void commandLineParser(int ac, char const **av);

        [[nodiscard]] std::string getScenePath() const { return m_scenePath; }
        [[nodiscard]] std::string getFormat() const { return m_format; }

    private:

        void parseOption(int ac, char const **av, int &i);

        static const std::array<std::string, 4> formatSupported;

        std::string m_scenePath;
        std::string m_format;
    };
}
