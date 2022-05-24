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