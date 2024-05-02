/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Matrix
*/

#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <functional>
#include <ostream>
#include <stdexcept>

namespace Math {
/// @brief Class used calculs and computations of Matrix of any dimension.
///        This class can also describe Vectors of any dimension.
/// @tparam ROW Number of rows of the matrix.
/// @tparam COL Number of columns of the matrix.
template <size_t ROW, size_t COL>
class Matrix {
public:
    Matrix() = default;

    Matrix(std::initializer_list<double> val)
    {
        size_t idx = 0;

        if (!val.size() || val.size() != ROW * COL)
            throw std::runtime_error("Incorrect number of argument.\n");
        for (auto value : val) {
            this->m_data[idx] = value;
            idx++;
        }
    }

    Matrix(const Matrix<ROW, COL> &) = default;

    Matrix(Matrix<ROW, COL> &&oth) : m_data(oth.m_data)
    {
    }

    ~Matrix() = default;

    double length() const
    {
        double sum = 0.f;
        for (size_t row = 0; row < ROW; row++) {
            sum += this->operator()(row, 0) * this->operator()(row, 0);
        }
        return sqrt(sum);
    }

    void normalize()
    {
        double len = length();

        if (!len)
            return;
        this->operator/=(len);
    }

    Math::Matrix<ROW, COL> normalized() const
    {
        double len = length();

        if (!len)
            return *this;
        return this->operator/(len);
    }

    /// @brief Dot product between 2 Vectors of N rows.
    ///        The current Matrix and the one passed as argument
    ///        MUST be vectors of same dimensions.
    double dot(const Matrix<ROW, 1> &vect) const
    {
        if (COL != 1) {
            throw std::runtime_error("Matrix must only have 1 Column.\n");
        }
        auto it_this = this->m_data.begin();
        auto it_mat = vect.m_data.begin();
        double res = 0.f;

        while (it_this != this->m_data.end() && it_mat != vect.m_data.end()) {
            res += (*it_mat) * (*it_this);
            it_mat++;
            it_this++;
        }
        return res;
    }

    /// @brief This function is used for Matrix Multiplication and can be used
    /// by vectors as well
    ///        as long as they respect the correct shapes.
    /// @tparam NEW_COL Number of columns of the Matrix passed as parameter.
    /// @param mat Matrix parameter used for computation.
    /// @return New matrix that is the result of the matrix multiplication.
    template <size_t NEW_COL>
    Matrix<ROW, NEW_COL> matMul(const Matrix<COL, NEW_COL> &mat)
    {
        Matrix<ROW, NEW_COL> newMat;

        for (size_t i = 0; i < ROW; i++) {
            for (size_t j = 0; j < COL; j++) {
                for (size_t k = 0; k < NEW_COL; k++) {
                    newMat(i, k) +=
                        this->operator()(i, j) * mat.operator()(j, k);
                }
            }
        }
        return newMat;
    }

    Matrix<ROW, COL> getVectorTo(const Matrix<ROW, COL> &vect) const
    {
        return vect - *this;
    }

    Matrix<ROW, COL> getVectorFrom(const Matrix<ROW, COL> &vect) const
    {
        return *this - vect;
    }

    Matrix<ROW, COL> &operator=(const Matrix<ROW, COL> &oth)
    {
        this->m_data = oth.m_data;
        return *this;
    }

    Matrix<ROW, COL> &operator=(Matrix<ROW, COL> &&oth)
    {
        this->m_data = oth.m_data;
        return *this;
    }

    Matrix<ROW, COL> operator+(const Matrix<ROW, COL> &oth) const
    {
        return do_opCreate(oth, std::plus<double>());
    }
    Matrix<ROW, COL> operator-(const Matrix<ROW, COL> &oth) const
    {
        return do_opCreate(oth, std::minus<double>());
    }
    Matrix<ROW, COL> operator*(const Matrix<ROW, COL> &oth) const
    {
        return do_opCreate(oth, std::multiplies<double>());
    }
    Matrix<ROW, COL> operator/(const Matrix<ROW, COL> &oth) const
    {
        return do_opCreate(oth, std::divides<double>());
    }

    Matrix<ROW, COL> &operator+=(const Matrix<ROW, COL> &oth)
    {
        return do_opThis(oth, std::plus<double>());
    }
    Matrix<ROW, COL> &operator-=(const Matrix<ROW, COL> &oth)
    {
        return do_opThis(oth, std::minus<double>());
    }
    Matrix<ROW, COL> &operator*=(const Matrix<ROW, COL> &oth)
    {
        return do_opThis(oth, std::multiplies<double>());
    }
    Matrix<ROW, COL> &operator/=(const Matrix<ROW, COL> &oth)
    {
        return do_opThis(oth, std::divides<double>());
    }

    Matrix<ROW, COL> operator+(double val) const
    {
        return do_opCreateValue([val](auto elem) -> double {
            return elem + val;
        });
    }
    Matrix<ROW, COL> operator-(double val) const
    {
        return do_opCreateValue([val](auto elem) -> double {
            return elem - val;
        });
    }
    Matrix<ROW, COL> operator*(double val) const
    {
        return do_opCreateValue([val](auto elem) -> double {
            return elem * val;
        });
    }

    Matrix<ROW, COL> operator/(double val) const
    {
        return do_opCreateValue([val](auto elem) -> double {
            return elem / val;
        });
    }

    Matrix<ROW, COL> &operator+=(double val)
    {
        return do_opThisValue([val](auto elem) -> double {
            return elem + val;
        });
    }
    Matrix<ROW, COL> &operator-=(double val)
    {
        return do_opThisValue([val](auto elem) -> double {
            return elem - val;
        });
    }
    Matrix<ROW, COL> &operator*=(double val)
    {
        return do_opThisValue([val](auto elem) -> double {
            return elem * val;
        });
    }
    Matrix<ROW, COL> &operator/=(double val)
    {
        return do_opThisValue([val](auto elem) -> double {
            return elem / val;
        });
    }

    inline double operator()(size_t i, size_t j) const
    {
        if (i >= ROW || j >= COL) {
            throw std::runtime_error("Out of bound.\n");
        }
        return this->m_data[i * COL + j];
    }

    inline double &operator()(size_t i, size_t j)
    {
        if (i >= ROW || j >= COL) {
            throw std::runtime_error("Out of bound.\n");
        }
        return this->m_data[i * COL + j];
    }

    /// @brief Swap the inner raw data array of the matrix with the one passed
    ///        as parameter.
    /// @param array Array containing the raw data that will be swapped.
    void swapData(std::array<double, ROW * COL> &array)
    {
        this->m_data.swap(array);
    }

    std::array<double, ROW * COL> &getRawData()
    {
        return m_data;
    }

    /// @brief Add a row to the current Matrix.
    /// @return A new matrix with ROW + 1 rows and COL columns.
    Matrix<ROW + 1, COL> addRow() const
    {
        size_t idx = 0;
        size_t endLine = 0;
        Matrix<ROW + 1, COL> mat;
        auto &arr = mat.getRawData();

        for (; idx < ROW * COL; idx++) {
            arr[idx] = this->m_data[idx];
        }
        for (; endLine < COL - 1; endLine++) {
            arr[idx + endLine] = 0;
        }
        arr[idx + endLine] = 1;
        return mat;
    }

private:
    // Do op functions are used to factorize code.

    template <typename F>
    Matrix<ROW, COL> do_opCreateValue(F func) const
    {
        Matrix<ROW, COL> mat(*this);

        std::transform(mat.m_data.begin(),
                       mat.m_data.end(),
                       mat.m_data.begin(),
                       func);
        return mat;
    }

    template <typename F>
    Matrix<ROW, COL> do_opCreate(const Matrix<ROW, COL> &oth, F func) const
    {
        Matrix<ROW, COL> mat;

        do_op(mat, oth, func);
        return mat;
    }

    template <typename F>
    Matrix<ROW, COL> &do_opThisValue(F func)
    {
        std::transform(this->m_data.begin(),
                       this->m_data.end(),
                       this->m_data.begin(),
                       func);
        return *this;
    }

    template <typename F>
    Matrix<ROW, COL> &do_opThis(const Matrix<ROW, COL> &oth, F func)
    {
        do_op(*this, oth, func);
        return *this;
    }

    template <typename F>
    void
    do_op(Matrix<ROW, COL> &mat, const Matrix<ROW, COL> &oth, F func) const
    {
        auto it_mat = this->m_data.begin();
        auto it_oth = oth.m_data.begin();
        size_t idx = 0;

        while (it_mat != mat.m_data.end() && it_oth != oth.m_data.end()) {
            mat.m_data[idx] = func((*it_mat), (*it_oth));
            it_mat++;
            it_oth++;
            idx++;
        }
    }

    /// @brief Raw data of the matrix.
    std::array<double, ROW * COL> m_data;
};
} // namespace Math

template <size_t ROW, size_t COL>
std::ostream &operator<<(std::ostream &s, const Math::Matrix<ROW, COL> &oth)
{
    s << "[" << std::endl;
    for (size_t i = 0; i < ROW; i++) {
        s << "   [";
        for (size_t j = 0; j < COL; j++) {
            s << oth(i, j);
            if (j != COL - 1) {
                s << ", ";
            }
        }
        s << "]";
        if (i != ROW - 1) {
            s << ",";
        }
        s << std::endl;
    }
    s << "]" << std::endl;
    return s;
}

/// @brief Alias of Matrix<3, 1> for 3D Vectors.
typedef Math::Matrix<3, 1> Vector3D;

/// @brief Alias of Matrix<4, 1> for 3D Vectors.
typedef Math::Matrix<4, 1> Vector4D;

/// @brief Alias of Matrix<3, 1> for 3D Points.
typedef Math::Matrix<3, 1> Point3D;

// Correctly defined outside the class template definition
template <size_t ROW, size_t COL>
Math::Matrix<ROW, COL> operator*(const Math::Matrix<ROW, COL>& mat, double scalar) {
    Math::Matrix<ROW, COL> result;
    for (size_t i = 0; i < ROW * COL; ++i) {
        result.m_data[i] = mat.m_data[i] * scalar;
    }
    return result;
}

template <size_t ROW, size_t COL>
Math::Matrix<ROW, COL> operator*(double scalar, const Math::Matrix<ROW, COL>& mat) {
    return mat * scalar;
}
