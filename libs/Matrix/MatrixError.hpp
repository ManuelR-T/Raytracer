/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MatrixError
*/

#include <exception>
#include <string>

namespace Error {
    class MatrixError: public std::exception {
    public:
        MatrixError(const std::string &errMsg):
            m_type("[ValueNotFound]: "),
            m_errMsg(errMsg)
        {
            formatErrMess();
        }

        const char *what() const noexcept override { return m_errMsg.c_str(); };
    private:
        virtual void formatErrMess() noexcept { m_errMsg = m_type + m_errMsg; }

        std::string m_type;
        std::string m_errMsg;
    };
}
