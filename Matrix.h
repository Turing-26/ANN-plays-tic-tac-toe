/**
 * @file Matrix.hame
 * @brief created a matrix data type to make calculations easier
 * @date 2022-05-26
 *
 */

#pragma once
#include <vector>
#include <cmath>
#include <functional>

class Matrix
{
    int rows;
    int cols;
    std::vector<float> values;

public:
    Matrix() : rows(0), cols(0), values({}) {}
    Matrix(int row, int col) : rows(row), cols(col), values({})
    {
        values.resize(cols * rows, 0);
    }

    std::vector<float> getVals()
    {
        return values;
    }

    void setVal(float in, int i)
    {
        values[i] = in;
    }

    float &at(int row, int col)
    {
        return values[row * cols + col];
    }

    /**
     * @brief multies the matrixes one called by the function and one passed in the parameter.
     * @param mat2
     * @return Matrix
     */

    Matrix mult(Matrix &mat2)
    {
        if (cols == mat2.rows)
        {
            Matrix res(rows, mat2.cols);

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < mat2.cols; j++)
                {
                    for (int k = 0; k < cols; k++)
                    {
                        res.at(i, j) += at(i, k) * mat2.at(k, j);
                    }
                }
            }
            return res;
        }
        return *this;
    }

    /**
     * @brief multiplies our desired matrix with the float value passed.
     *
     * @param val
     * @return Matrix
     */

    Matrix mult(float val)
    {
        Matrix res(rows, cols);

        for (int i = 0; i < res.rows; i++)
        {
            for (int j = 0; j < res.cols; j++)
            {
                res.at(i, j) = this->at(i, j) * val;
            }
        }
        return res;
    }

    Matrix multEl(Matrix &mat2)
    {
        if (rows == mat2.rows && cols == mat2.cols)
        {
            Matrix res(rows, cols);

            for (int i = 0; i < mat2.rows; i++)
            {
                for (int j = 0; j < mat2.cols; j++)
                {
                    res.at(i, j) = this->at(i, j) * mat2.at(i, j);
                }
            }
            return res;
        }
        return *this;
    }

    /**
     * @brief add our desired two matrixes one called by the function and on passed to the function.
     *
     * @param mat2
     * @return Matrix
     */

    Matrix add(Matrix &mat2)
    {
        if (rows == mat2.rows && cols == mat2.cols)
        {
            Matrix res(rows, cols);

            for (int i = 0; i < mat2.rows; i++)
            {
                for (int j = 0; j < mat2.cols; j++)
                {
                    res.at(i, j) = this->at(i, j) + mat2.at(i, j);
                }
            }
            return res;
        }
        return *this;
    }

    /**
     * @brief it add a float passed value in our matrix .
     *
     * @param val
     * @return Matrix
     */

    Matrix add(float val)
    {
        Matrix res(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                res.at(i, j) = this->at(i, j) + val;
            }
        }
        return res;
    }

    /**
     * @brief it turns all the vales of a matrix into it -(ve) counterparts.
     *
     * @return Matrix
     */
    Matrix neg()
    {
        Matrix res(rows, cols);

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                res.at(i, j) = (this->at(i, j)) * -1;
            }
        }
        return res;
    }

    /**
     * @brief it takes the transpose of the matrix that calls the function.
     *
     * @return Matrix
     */

    Matrix trans()
    {
        Matrix res(cols, rows);

        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                res.at(i, j) = this->at(j, i);
            }
        }
        return res;
    }

/**
 * @brief applies the function passed into the parameter.
 */

    Matrix apply(float (*func)(const float))
    {
        Matrix res(rows, cols);

        for (int i = 0; i < res.rows; i++)
        {
            for (int j = 0; j < res.cols; j++)
            {
                res.at(i, j) = func(this->at(i, j));
            }
        }
        return res;
    }
};